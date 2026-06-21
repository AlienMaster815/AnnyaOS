#include <check.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Test that memory allocation functions do not hang indefinitely */
START_TEST(test_msvcrt_memory_functions_do_not_hang)
{
    /* Invariant: malloc(), calloc(), and free() must not enter infinite loops
       that cause the process to hang permanently. The security boundary requires
       that these fundamental C runtime functions either return or fail gracefully,
       not deadlock the entire application. */
    
    const char *test_cases[] = {
        "malloc",      /* exact exploit case: malloc stub enters while(1) */
        "calloc",      /* boundary case: calloc stub enters while(1) */
        "free",        /* valid input case: free stub enters while(1) */
    };
    int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_cases; i++) {
        pid_t pid = fork();
        ck_assert_int_ne(pid, -1);
        
        if (pid == 0) {
            /* Child process: attempt to call the function with timeout */
            alarm(2);  /* 2-second timeout */
            
            if (strcmp(test_cases[i], "malloc") == 0) {
                malloc();
            } else if (strcmp(test_cases[i], "calloc") == 0) {
                calloc();
            } else if (strcmp(test_cases[i], "free") == 0) {
                free();
            }
            
            exit(0);  /* Should not reach here if function hangs */
        } else {
            /* Parent process: wait for child with timeout */
            int status;
            int result = waitpid(pid, &status, 0);
            
            /* Verify child did not hang (would be killed by alarm) */
            ck_assert_int_ne(result, -1);
            ck_assert(WIFEXITED(status) || WIFSIGNALED(status));
            
            /* If killed by signal, it hung (SIGALRM = 14) */
            if (WIFSIGNALED(status)) {
                int sig = WTERMSIG(status);
                ck_assert_msg(sig != SIGALRM, 
                    "Function %s entered infinite loop and hung", test_cases[i]);
            }
        }
    }
}
END_TEST

Suite *security_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Security");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_msvcrt_memory_functions_do_not_hang);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = security_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}