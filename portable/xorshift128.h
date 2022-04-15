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

uint32_t rng_xor128_state[4]={0x81300422,0x49680d02,0x827b0548,0xe9c907f0};

SHL uint32_t rng_xor128(uint32_t n){
	return rng_xor128_u32(rng_xor128_state)/(UINT32_MAX/n);
}
