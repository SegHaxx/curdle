#include <limits.h>

uint32_t rng_xor128_state[4]={0x2404848,0x4522ed14,0x81300422,0x44ea35b};

// from pg5 of Marsaglia, "Xorshift RNGs"
static uint32_t rng_xor128_u32(void){
	uint32_t* state=rng_xor128_state;
	uint32_t t = state[3];
	uint32_t const s = state[0];
	state[3] = state[2];
	state[2] = state[1];
	state[1] = s;
	t ^= t << 11;
	t ^= t >> 8;
	return state[0] = t ^ s ^ (s >> 19);
}

SHL uint32_t rng_xor128(uint32_t n){
	return (rng_xor128_u32()-1)/((UINT32_MAX-1)/(n-1));
}
