[bits 64]



section .data

global InterruptCode
raxp dq 0
global InterruptNum
global InstructionPointer
global ThreadStart
global RSPPoint

InterruptMutex dq 0

InterruptNum db 0
InterruptCode dq 0
InstructionPointer dq 0

global SYSTEMCALL

SYSTEMCALL dq 0

savedRIP dq 0 

RSPPoint dq 0

section .bss

section .text
extern InterruptRouter
extern PIC_sendEOI
extern UpdateThreadManager

FPU_ON dq 0
SSE_ON dq 0
AVX_OM dq 0

global TURN_FPU_ON

TURN_FPU_ON:
	mov rax, 1
	mov [FPU_ON], rax
	ret

%macro pusha 0	

	push r15
	push r14
	push r13
	push r12
	push r11
	push r10
	push r9
	push r8

	push rdi
	push rsi
	push rbp

	push rdx
	push rcx
	push rbx
	push rax

%endmacro

%macro popa 0

	pop rax
	pop rbx
	pop rcx
	pop rdx

	pop rbp
	pop rsi
	pop rdi

	pop r8
	pop r9
	pop r10
	pop r11
	pop r12
	pop r13
	pop r14
	pop r15

%endmacro

;PIC_sendEOI(unsigned char irq)

%macro Handle 0
	pop rcx
	mov rdx, rsp
	call InterruptRouter
%endmacro

global ISR0
global ISR1
global ISR2
global ISR3
global ISR4
global ISR5
global ISR6
global ISR7
global ISR8
global ISR9
global ISR10
global ISR11
global ISR12
global ISR13
global ISR14
global ISR15
global ISR16
global ISR17
global ISR18
global ISR19
global ISR20
global ISR21
global ISR22
global ISR23
global ISR24
global ISR25
global ISR26
global ISR27
global ISR28
global ISR29
global ISR30
global ISR31



global ISR32
global ISR33
global ISR34
global ISR35
global ISR36
global ISR37
global ISR38
global ISR39
global ISR40
global ISR41
global ISR42
global ISR43
global ISR44
global ISR45
global ISR46
global ISR47
global ISR48
global ISR49
global ISR50

global ISR51
global ISR52
global ISR53
global ISR54
global ISR55
global ISR56
global ISR57
global ISR58
global ISR59
global ISR60
global ISR61
global ISR62
global ISR63
global ISR64
global ISR65
global ISR66
global ISR67
global ISR68
global ISR69
global ISR70
global ISR71
global ISR72
global ISR73
global ISR74
global ISR75
global ISR76
global ISR77
global ISR78
global ISR79
global ISR80
global ISR81
global ISR82
global ISR83
global ISR84
global ISR85
global ISR86
global ISR87
global ISR88
global ISR89
global ISR90
global ISR91
global ISR92
global ISR93
global ISR94
global ISR95
global ISR96
global ISR97
global ISR98
global ISR99
global ISR100
global ISR101
global ISR102
global ISR103
global ISR104
global ISR105
global ISR106
global ISR107
global ISR108
global ISR109
global ISR110
global ISR110
global ISR111
global ISR112
global ISR113
global ISR114
global ISR115
global ISR116
global ISR117
global ISR118
global ISR119
global ISR120
global ISR121
global ISR122
global ISR123
global ISR124
global ISR125
global ISR126
global ISR127
global ISR128
global ISR129
global ISR130
global ISR131
global ISR132
global ISR133
global ISR134
global ISR135
global ISR136
global ISR137
global ISR138
global ISR139
global ISR140
global ISR141
global ISR142
global ISR143
global ISR144
global ISR145
global ISR146
global ISR147
global ISR148
global ISR149
global ISR150
global ISR151
global ISR152
global ISR153
global ISR154
global ISR155
global ISR156
global ISR157
global ISR158
global ISR159
global ISR160
global ISR161
global ISR162
global ISR163
global ISR164
global ISR165
global ISR166
global ISR167
global ISR168
global ISR169
global ISR170
global ISR171
global ISR172
global ISR173
global ISR174
global ISR175
global ISR176
global ISR177
global ISR178
global ISR179
global ISR180
global ISR181
global ISR182
global ISR183
global ISR184
global ISR185
global ISR186
global ISR187
global ISR188
global ISR189
global ISR190
global ISR191
global ISR192
global ISR193
global ISR194
global ISR195
global ISR196
global ISR197
global ISR198
global ISR199
global ISR200

global HandleSwitch
global StoreContext 

global ContextLiftoff
extern RegisterLastKnownStackLocation
section .text
global getRsp

SaveNext dd 0

ContextLiftoff:
	pusha
	mov [rdx], rsp
	mov rsp, rcx;
    popa
	ret

ThreadStart:

	popa	
	iretq

ISR0:
	
	pusha
	push 0
	mov [InterruptNum], ah
	Handle

ISR1:
	
	pusha
	push 1
	mov [InterruptNum], ah
	popa

ISR2:
	
	pusha
	push 2
	mov [InterruptNum], ah
	Handle

ISR3:
	
	pusha
	push 3
	mov [InterruptNum], ah
	Handle

ISR4:
	
	pusha
	push 4
	mov [InterruptNum], ah
	Handle

ISR5:
	
	pusha
	push 5
	mov [InterruptNum], ah
	Handle

ISR6:
	
	pusha
	push 6
	mov [InterruptNum], ah
	Handle

ISR7:
	
	pusha
	push 7
	mov [InterruptNum], ah
	Handle
	popa	
	iretq
ISR8:
	
	pusha
	push 8
	mov [InterruptNum], ah
	Handle

ISR9:
	
	pusha
	push 9
	mov [InterruptNum], ah
	Handle

ISR10:
	
	pusha
	push 10
	mov [InterruptNum], ah
	Handle

ISR11:
	
	pusha
	push 11
	mov [InterruptNum], ah
	Handle

ISR12:
	
	pusha
	push 12
	mov [InterruptNum], ah
	Handle

ISR13:
	;GPF
	pusha
	push 13
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR14:
	
	mov [raxp], rax
    pop rax
    mov [InterruptCode], rax
    xor rax, rax
    mov rax, [raxp]
    pusha
    push 14
    mov [InterruptNum], ah
    Handle
    popa
    iretq

ISR15:
	
	pusha
	push 15
	mov [InterruptNum], ah
	Handle

ISR16:
	
	pusha
	push 16
	mov [InterruptNum], ah
	Handle

ISR17:
	
	pusha
	push 17
	mov [InterruptNum], ah
	Handle

ISR18:
	
	pusha
	push 18
	mov [InterruptNum], ah
	Handle

ISR19:
	
	pusha
	push 19
	mov [InterruptNum], ah
	jmp Handle

ISR20:
	
	pusha
	push 20
	mov [InterruptNum], ah
	Handle

ISR21:
	
	pusha
	push 21
	mov [InterruptNum], ah
	Handle

ISR22:
	
	pusha
	push 22
	mov [InterruptNum], ah
	Handle

ISR23:
	
	pusha
	push 23
	mov [InterruptNum], ah
	Handle

ISR24:
	
	pusha
	push 24
	mov [InterruptNum], ah
	Handle

ISR25:
	
	pusha
	push 25
	mov [InterruptNum], ah
	Handle

ISR26:
	
	pusha
	push 26
	mov [InterruptNum], ah
	Handle

ISR27:
	
	pusha
	push 27
	mov [InterruptNum], ah
	Handle

ISR28:
	
	pusha
	push 28
	mov [InterruptNum], ah
	Handle

ISR29:
	
	pusha
	push 29
	mov [InterruptNum], ah
	Handle

ISR30:
	
	pusha
	push 30
	mov [InterruptNum], ah
	Handle

ISR31:
	
	pusha
	push 31
	mov [InterruptNum], ah
	Handle





ISR32:
	pusha
	mov rcx, rsp
	call UpdateThreadManager  
	mov rsp, rax 
	popa                                                                                              
	iretq

ISR33:
	
	pusha
	push 33
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR34:
	
	pusha
	push 34
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR35:
	pusha
	push 35
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR36:
	
	pusha
	push 36
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR37:
	
	pusha
	push 37
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR38:
	
	pusha
	push 38
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR39:
	pusha
	push 39
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR40:
	
	pusha	
	push 40
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR41:
	pusha
	push 41
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR42:
	
	pusha
	push 42
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR43:
	
	pusha	
	push 43
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR44:
	pusha	
	push 44
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR45:
	
	pusha
	push 45
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR46:
	pusha
	push 46
	mov [InterruptNum], ah
	Handle
	popa	
	iretq
	
ISR47:
	pusha
	push 47
	mov [InterruptNum], ah
	Handle
	popa	
	iretq
	
ISR48:
	pusha
	push 48
	mov [InterruptNum], ah
	Handle
	popa	
	iretq
	

ISR49:
	
	pusha
	push 49
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR50:
	
	pusha
	push 50
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR51:
	
	pusha
	push 51
	mov [InterruptNum], ah
	Handle
	popa	
	iretq


ISR52:
	
	pusha
	push 52
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR53:
	
	pusha
	push 53
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR54:
	
	pusha
	push 54
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR55:
	
	pusha
	push 55
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR56:
	
	pusha
	push 56
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR57:
	
	pusha
	push 57
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR58:
	
	pusha
	push 58
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR59:
	
	pusha
	push 59
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR60:
	
	pusha
	push 60
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR61:
	
	pusha
	push 61
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR62:
	
	pusha
	push 62
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR63:
	
	pusha
	push 63
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR64:
	
	pusha
	push 64
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR65:
	
	pusha
	push 65
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR66:
	
	pusha
	push 66
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR67:
	
	pusha
	push 67
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR68:
	
	pusha
	push 68
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR69:
	
	pusha
	push 69
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR70:
	
	pusha
	push 70
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR71:
	 ;This is an issue
	pusha
	push 71
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR72:
	
	pusha
	push 72
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR73:
	
	pusha
	push 73
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR74:
	
	pusha
	push 74
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR75:
	
	pusha
	push 75
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR76:
	
	pusha
	push 76
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR77:
	
	pusha
	push 77
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR78:
	
	pusha
	push 78
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR79:
	
	pusha
	push 79
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR80:
	
	pusha
	push 80
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR81:
	
	pusha
	push 81
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR82:
	
	pusha
	push 82
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR83:
	
	pusha
	push 83
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR84:
	
	pusha
	push 84
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR85:
	
	pusha
	push 85
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR86:
	
	pusha
	push 86
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR87:
	
	pusha
	push 87
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR88:
	
	pusha
	push 88
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR89:
	
	pusha
	push 89
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR90:
	
	pusha
	push 90
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR91:
	
	pusha
	push 91
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR92:
	
	pusha
	push 92
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR93:
	
	pusha
	push 93
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR94:
	
	pusha
	push 94
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR95:
	
	pusha
	push 95
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR96:
	
	pusha
	push 96
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR97:
	
	pusha
	push 97
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR98:
	
	pusha
	push 98
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR99:
	
	pusha
	push 99
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR100:
	
	pusha
	push 100
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR101:
	
	pusha
	push 101
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR102:
	
	pusha
	push 102
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR103:
	
	pusha
	push 103
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR104:
	
	pusha
	push 104
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR105:
	
	pusha
	push 105
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR106:
	
	pusha
	push 106
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR107:
	
	pusha
	push 107
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR108:
	
	pusha
	push 108
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR109:
	
	pusha
	push 109
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR110:
	
	pusha
	push 110
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR111:
	
	pusha
	push 111
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR112:
	
	pusha
	push 112
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR113:
	
	pusha
	push 113
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR114:
	
	pusha
	push 114
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR115:
	
	pusha
	push 115
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR116:
	
	pusha
	push 116
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR117:
	
	pusha
	push 117
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR118:
	
	pusha
	push 118
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR119:
	
	pusha
	push 119
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR120:
	
	pusha
	push 120
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR121:
	
	pusha
	push 121
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR122:
	
	pusha
	push 122
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR123:
	
	pusha
	push 123
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR124:
	
	pusha
	push 124
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR125:
	
	pusha
	push 125
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR126:
	
	pusha
	push 126
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

;Smp Interrupts
ISR127:
	
	pusha
	push 127
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

extern SYSCALLS

ISR128:
	pusha
	mov r9, rsp
	call SYSCALLS
	popa	
	iretq

ISR129:
	pusha
	push rdx
	push rsi
	push rdi
	pop rcx
	pop rdx
	pop r8
	mov r9, rsp
	call SYSCALLS
	popa	
	iretq

ISR130:
	pusha
	mov r9, rsp
	;call SYSCALLS32 ;todo implement 32 bit syscalls
	popa	
	iretq

ISR131:
	pusha
	push rdx
	push rsi
	push rdi
	pop rcx
	pop rdx
	pop r8
	mov r9, rsp
	;call SYSCALLS32 todo Add 32 bit syscalls
	popa	
	iretq

ISR132:
	
	pusha
	push 132
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR133:
	
	pusha
	push 133
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR134:
	
	pusha
	push 134
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR135:
	
	pusha
	push 135
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR136:
	
	pusha
	push 136
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR137:
	
	pusha
	push 137
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR138:
	
	pusha
	push 138
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR139:
	
	pusha
	push 139
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR140:
	
	pusha
	push 140
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR141:
	
	pusha
	push 141
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR142:
	
	pusha
	push 142
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR143:
	
	pusha
	push 143
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR144:
	
	pusha
	push 144
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR145:
	 
	pusha
	push 145
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR146:
	 
	pusha
	push 146
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR147:
	 
	pusha
	push 147
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR148:
	 
	pusha
	push 148
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR149:
	 
	pusha
	push 149
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR150:
	 
	pusha
	push 150
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR151:
	 
	pusha
	push 151
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR152:
	 
	pusha
	push 152
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR153:
	 
	pusha
	push 153
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR154:
	 
	pusha
	push 154
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR155:
	 
	pusha
	push 155
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR156:
	 
	pusha
	push 156
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR157:
	 
	pusha
	push 157
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR158:
;	popa	
	iretq 
	pusha
	push 158
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR159:
;	popa	
	iretq 
	pusha
	push 159
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR160:
;	popa	
	iretq 
	pusha
	push 160
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR161:
;	popa	
	iretq 
	pusha
	push 161
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR162:
;	popa	
	iretq
	pusha
	push 162
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR163:
;	popa	
	iretq
	pusha
	push 163
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR164:
;	popa	
	iretq 
	pusha
	push 164
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR165:
;	popa	
	iretq 
	pusha
	push 165
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR166:
;	popa	
	iretq 
	pusha
	push 166
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR167:
;	popa	
	iretq 
	pusha
	push 167
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR168:
;	popa	
	iretq 
	pusha
	push 168
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR169:
;	popa	
	iretq 
	pusha
	push 169
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR170:
;	popa	
	iretq 
	pusha
	push 170
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR171:
;	popa	
	iretq 
	pusha
	push 171
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR172:
;	popa	
	iretq 
	pusha
	push 172
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR173:
;	popa	
	iretq 
	pusha
	push 173
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR174:
;	popa	
	iretq 
	pusha
	push 174
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR175:
;	popa	
	iretq 
	pusha
	push 175
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR176:
;	popa	
	iretq 
	pusha
	push 176
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR177:
;	popa	
	iretq 
	pusha
	push 177
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR178:
;	popa	
	iretq 
	pusha
	push 8
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR179:
;	popa	
	iretq 
	pusha
	push 179
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR180:
;	popa	
	iretq 
	pusha
	push 180
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR181:
;	popa	
	iretq 
	pusha
	push 181
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR182:
;	popa	
	iretq 
	pusha
	push 182
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR183:
;	popa	
	iretq 
	pusha
	push 183
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR184:
;	popa	
	iretq 
	pusha
	push 184
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR185:
;	popa	
	iretq 
	pusha
	push 185
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR186:
;	popa	
	iretq 
	pusha
	push 186
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR187:
;	popa	
	iretq 
	pusha
	push 187
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR188:
;	popa	
	iretq 
	pusha
	push 188
 	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR189:
;	popa	
	iretq 
	pusha
	push 189
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR190:
;	popa	
	iretq 
	pusha
	push 190
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR191:
;	popa	
	iretq 
	pusha
	push 191
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR192:
;	popa	
	iretq
	pusha
	push 192
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR193:
;	popa	
	iretq 
	pusha
	push 193
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR194:
;	popa	
	iretq 
	pusha
	push 194
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR195:
;	popa	
	iretq 
	pusha
	push 195
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR196:
;	popa	
	iretq 
	pusha
	push 196
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR197:
;	popa	
	iretq 
	pusha
	push 197
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR198:
;	popa	
	iretq 
	pusha
	push 198
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR199:
;	popa	
	iretq 
	pusha
	push 199
	mov [InterruptNum], ah
	Handle
	popa	
	iretq

ISR200:
;	popa	
	iretq
	pusha
	push 200
	mov [InterruptNum], ah
	Handle
	popa	
	iretq