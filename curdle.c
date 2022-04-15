// Copyright 2022 Seg <seg@haxxed.com>
#include "portable/term.h"

static char banner[]=NL
"curdle: (intransitive verb)" NL
"To become spoiled or transformed into something bad" NL;

#include "portable/input.h"
#include "portable/xorshift128.h"

#include "curdlist.h"

static void curd_pack(char* word,unsigned char* curd){
	uint32_t base26=0L;
	for(int i=0;i<5;++i){
		base26*=26;base26+=((uint32_t)(word[i]&=0xdf))-'A';}
	curd[0]=base26>>16;curd[1]=base26>>8;curd[2]=base26;}

static void curd_unpack(const unsigned char* curd,char* word){
	uint32_t base26=((uint32_t)curd[0]<<16)+
		((uint32_t)curd[1]<<8)+(uint32_t)curd[2];
	char* tmp=word+5;do{*--tmp='A'+(base26%26);base26/=26;}
	while(tmp>word);}

static void word_print(char* p){for(int i=0;i<5;++i)printc(p[i]);}

SHL void curdlist_print(){
	for(int i=0;i<curdlist_count;++i){
		//word_print(&curdlist[i*5L]);print(NL);
		}}

static int curd_compare(unsigned char* a,unsigned char* b){
	if(a[0]!=b[0]) return 1;if(a[1]!=b[1]) return 1;
	if(a[2]!=b[2]) return 1;return 0;}

static int curdlist_search(char* guess){
	unsigned char pguess[3];curd_pack(guess,pguess);
	for(int i=0;i<curdlist_count;++i){
		if(!curd_compare(pguess,&curdlist[i*3L])) return 1;}
	return 0;}

static void curd_pick(char* word){
	uint32_t n=rng_xor128(curdlist_count);//n=5847;
	curd_unpack(&curdlist[n*3L],word);
	word_print(word);printc(' ');
	print_u32(n);print(NL NL);}

static void do_wordle(){char s[5];curd_pick(s);
	char nope[1+'Z'-'A']={0};char* n=(char*)&nope;n-='A';
	INPUT_T inp;inp.maxlen=5;while(1){input(&inp);
		if(inp.actuallen<5) continue;char* guess=inp.buffer;
		if(!curdlist_search(guess)){print(NL "Not in list" NL);continue;}
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
	{print(NL "Guess the secret word:" NL);do_wordle();}return 0;}
