#include <LouAPI.h>


uint64_t xorshift(uint64_t state) {
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    // Ensure state is not zero
    if (state == 0) {
        state = 1; // or any other non-zero value
    }
    return state;
}

uint64_t LCG(
    uint64_t Seed, 
    uint64_t multiplier, 
    uint64_t Modulator, 
    uint64_t increment
){
    Seed = xorshift(Seed);
    multiplier = xorshift(multiplier);
    increment = xorshift(increment);
    Modulator = xorshift(Modulator);
    // Ensure Modulator is non-zero and a reasonable value
    Modulator = Modulator == 0 ? 1 : Modulator;
    return (multiplier * Seed + increment) % Modulator;
}



uint64_t Random(uint64_t Seed){
    // Dynamically generate LCG parameters
    uint64_t a = xorshift(Seed ^ (Seed << 21));
    uint64_t c = xorshift(Seed ^ (Seed >> 35));
    uint64_t m = xorshift(Seed ^ (Seed << 4));

    // Ensure parameters are non-zero
    a = a == 0 ? 1 : a;
    c = c == 0 ? 1 : c;
    m = m == 0 ? 1 : m;

    return LCG(Seed, a, c, m);
}


uint64_t QuantumRandomization(
    uint64_t Seed
){
    Seed = Random(Seed);
    Seed = Random(Seed);
    Seed = Random(Seed);
    Seed = Random(Seed);
    Seed = Random(Seed);
    
    return Seed;
}

#include <LouAPI.h>

uint32_t xorshift32(uint32_t state) {
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    // Ensure state is not zero
    if (state == 0) {
        state = 1; // or any other non-zero value
    }
    return state;
}

uint32_t LCG32(
    uint32_t Seed, 
    uint32_t multiplier, 
    uint32_t Modulator, 
    uint32_t increment
) {
    Seed = xorshift32(Seed);
    multiplier = xorshift32(multiplier);
    increment = xorshift32(increment);
    Modulator = xorshift32(Modulator);
    // Ensure Modulator is non-zero and a reasonable value
    Modulator = Modulator == 0 ? 1 : Modulator;
    return (multiplier * Seed + increment) % Modulator;
}

uint32_t Random32(uint32_t Seed) {
    // Dynamically generate LCG parameters
    uint32_t a = xorshift32(Seed ^ (Seed << 21));
    uint32_t c = xorshift32(Seed ^ (Seed >> 15));
    uint32_t m = xorshift32(Seed ^ (Seed << 4));

    // Ensure parameters are non-zero
    a = a == 0 ? 1 : a;
    c = c == 0 ? 1 : c;
    m = m == 0 ? 1 : m;

    return LCG32(Seed, a, c, m);
}

uint32_t QuantumRandomization32(
    uint32_t Seed
) {
    Seed = Random32(Seed);
    Seed = Random32(Seed);
    Seed = Random32(Seed);
    Seed = Random32(Seed);
    Seed = Random32(Seed);

    return Seed;
}

static uint32_t GlobalRandSeed;

void SetRANDSeed(uint32_t NewSeed){
    GlobalRandSeed = NewSeed;
}

uint32_t LouKeRandCStdLib(){
    return QuantumRandomization32(GlobalRandSeed);
}