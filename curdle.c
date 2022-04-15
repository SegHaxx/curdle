// Copyright 2022 Seg <seg@haxxed.com>
#include "portable/term.h"

static const char banner[]=NL
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

SHL void word_print(char* p){for(int i=0;i<5;++i)printc(p[i]);}

SHL void curdlist_print(){
	for(int i=0;i<curdlist_count;++i){unsigned char curd[3];
		curd[0]=curdlist0[i];curd[1]=curdlist1[i];curd[2]=curdlist2[i];
		char word[5];curd_unpack(curd,word);word_print(word);print(NL);}}

static int curd_compare(unsigned char* a,unsigned char* b){
	if(a[0]!=b[0]) return 1;if(a[1]!=b[1]) return 1;
	if(a[2]!=b[2]) return 1;return 0;}

static void curd_pick(char* word){
	uint32_t n=rng_xor128(curdlist_count);unsigned char curd[3];
	curd[0]=curdlist0[n];curd[1]=curdlist1[n];curd[2]=curdlist2[n];
	curd_unpack(curd,word);
	//print(NL);word_print(word);printc(' ');print_u32(n);print(NL);
}

static int curdlist_search(char* guess){
	unsigned char pguess[3];curd_pack(guess,pguess);
	for(int i=0;i<curdlist_count;++i){
		unsigned char curd[3]; curd[0]=curdlist0[i];
		curd[1]=curdlist1[i]; curd[2]=curdlist2[i];
		if(!curd_compare(pguess,curd)) return 1;}
	return 0;}

int8_t curd_hint[5];

// check a guess
static int curd_check(char* guess,char *secret){
	if(!curdlist_search(guess)){
		for(int i=0;i<5;++i)curd_hint[i]=0;return 2;}
	int win=0;
	for(int i=0;i<5;++i){
		int hint=0; // nope
		char g=guess[i];
		if(g==secret[i])hint=2; // correct
		else{for(int j=0;j<5;++j) if(g==secret[j])hint=1;} // wrong spot
		if(hint!=2)win=1;
		curd_hint[i]=hint;}
	return win;
}

static void do_curd(char* s){
	char nope[1+'Z'-'A']={0};char* n=(char*)&nope;n-='A';
	INPUT_T inp;inp.maxlen=5;while(1){input(&inp);
		if(inp.actuallen<5) continue;char* guess=inp.buffer;
		int lose=curd_check(guess,s);
		if(lose==2){print(NL "Not in list" NL);continue;}print(NL);
		for(int i=0;i<5;++i){int8_t h=curd_hint[i];char g=guess[i];
			if(h==0)n[(int)g]=g;term_bgcolor(curd_hint[i]);printc(g);}
		term_bgcolor(0);printc(' ');if(!lose)break;
		for(int i='A';i<='Z';++i)if(n[i])printc(n[i]);print(NL);}
	print("Correct!" NL);}

int main(){print(banner);while(1){char secret[5];curd_pick(secret);
	print(NL "Guess the secret word:" NL);do_curd(secret);}return 0;}
