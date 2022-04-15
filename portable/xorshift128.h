#include <limits.h>

// from pg5 of Marsaglia, "Xorshift RNGs"
static uint32_t rng_xor128_u32(uint32_t* state){
	uint32_t t = state[3];
	uint32_t const s = state[0];
	state[3] = state[2];
	state[2] = state[1];
	state[1] = s;
	t ^= t << 11;
	t ^= t >> 8;
	return state[0] = t ^ s ^ (s >> 19);
}

uint32_t rng_xor128_state[4]={0xabb41ca8,0x468a5b62,0x89b11400,0x6cb6b5d9};

SHL uint32_t rng_xor128(uint32_t n){
	return (rng_xor128_u32(rng_xor128_state)-1)/((UINT32_MAX-1)/(n-1));
}
