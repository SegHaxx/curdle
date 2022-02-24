// Copyright 2022 Seg <seg@haxxed.com>
#include "portable/term.h"

static char banner[]=NL
"curdle: (intransitive verb)" NL
"To become spoiled or transformed into something bad" NL;

#include "portable/input.h"
#include "portable/xorshift128.h"

#include "wordlist.h"

static void word_print(char* p){for(int i=0;i<5;++i)printc(p[i]);}

SHL void wordlist_print(){
	for(int i=0;i<wordlist_count;++i){
		word_print(&wordlist[i*5L]);print(NL);}}

static int word_compare(char* a, char* b){
	for(int i=0;i<5;++i) if((a[i]&=0xdf)!=b[i]) return 1;
	return 0;}

static int wordlist_search(char* guess){
	for(int i=0;i<wordlist_count;++i)
		if(!word_compare(guess,&wordlist[i*5L])) return 1;
	return 0;}

static char* word_pick(){
	uint32_t n=rng_xor128(wordlist_count);
	char* word=&wordlist[n*5L];
	//word_print(word);printc(' ');
	//print_u32(n);print(NL NL);
	return word;}

static void do_wordle(){char* s=word_pick();
	char nope[1+'Z'-'A']={0};char* n=(char*)&nope;n-='A';
	INPUT_T inp;inp.maxlen=5;while(1){input(&inp);
		if(inp.actuallen<5) continue;char* guess=inp.buffer;
		if(!wordlist_search(guess)){print(NL "Not in list" NL);continue;}
		print(NL);int8_t hint[5];
		for(int i=0;i<5;++i){int8_t h=0;char g=guess[i];
			if(g==s[i]){h=2;}else{for(int j=0;j<5;++j)if(g==s[j])h=1;}
			if(h==0) n[(int)g]=g;hint[i]=h;}
		int win=1;for(int i=0;i<5;++i){
			int h=hint[i];if(h!=2) win=0;term_bgcolor(h);printc(guess[i]);}
		term_bgcolor(0);printc(' ');if(win)break;
		for(int i='A';i<='Z';++i)if(n[i])printc(n[i]);print(NL);}
	print("Correct!" NL);}

int main(){print(banner);
	while(1){print(NL "Guess the secret word:" NL);do_wordle();}return 0;}
