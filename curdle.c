// Copyright 2022 Seg <seg@haxxed.com>
#include "portable/term.h"

static const char banner[]=NL
"curdle: (intransitive verb)" NL
"To become spoiled or transformed into something bad" NL;

#include "portable/input.h"
#include "portable/date.h"
#include "portable/timer.h"
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
	//word_print(word);printc(' ');print_u32(n);print(NL);
}

static int curdlist_search(char* guess){
	unsigned char pguess[3];curd_pack(guess,pguess);
	for(int i=0;i<curdlist_count;++i){
		unsigned char curd[3]; curd[0]=curdlist0[i];
		curd[1]=curdlist1[i]; curd[2]=curdlist2[i];
		if(!curd_compare(pguess,curd)) return 1;}
	return 0;}

// check a guess
static int curd_check(char* s,char *g,int8_t* h){
	if(!curdlist_search(g))return 2;for(int i=0;i<5;++i)h[i]=0;int l=0;
	for(int i=0;i<5;++i){if(s[i]==g[i]){h[i]=2;continue;}l=1;
	for(int j=0;j<5;++j)if((s[i]==g[j])&&!h[j]){h[j]=1;break;}}return l;}

static void hint_style(int h){switch(h){
		default:term_bgcolor(BR_BLACK);term_fgcolor(WHITE);return;
		case 1:term_bgcolor(YELLOW);break;
		case 2:term_bgcolor(GREEN);break;}term_fgcolor(BR_WHITE);}

#define GUESS_MAX 6

static int do_curd(char* s,int8_t* hint){print("Guess the secret word:" NL);
	char nope[1+'Z'-'A']={0};char* n=(char*)&nope;n-='A';int lose;
	INPUT_T inp;inp.maxlen=5;int gn=1;while(1){printi(gn);print("? ");
		input(&inp);if(inp.actuallen<5) continue;char* guess=inp.buffer;
		lose=curd_check(s,guess,hint);
		if(lose==2){print(NL "Not in list" NL);continue;}print(NL);++gn;
		for(int i=0;i<5;++i){int8_t h=hint[i];char g=guess[i];
			if(h==0)n[(int)g]=g;hint_style(hint[i]);printc(g);}
		term_nocolor();printc(' ');if(!lose)break;
		for(int i='A';i<='Z';++i)if(n[i])printc(n[i]);print(NL);
		if(gn>GUESS_MAX)break;hint+=5;}
	if(!lose)print("Correct!" NL);return gn-1;}

#if defined(__GNUC__) && defined(__OPTIMIZE_SIZE__)
__attribute__ ((noinline)) // no gcc don't inline it
#endif
static int is_ly(int y){return(!(y%400)||((y%100)&&!(y%4)))?1:0;}

static int date_in_days(int year,int month,int day){int d=-74;
	for(int y=1981;y<year;++y) d+=365+is_ly(y);if(--month>0) d+=is_ly(year);
	static char monthadj[12]={0,4,5,7,8,10,11,12,14,15,17,18};
	d+=month*32-monthadj[month];return d+day-1;}

static void do_daily(){
	int y,m,d;get_date(&y,&m,&d);print(NL "Today is ");
	printi(y);printc('-');printi(m);printc('-');printi(d);
	int curd=date_in_days(y,m,d);
	print(NL "Daily Curd #");printi(curd);print(NL NL);

	for(int i=0;i<curd;++i) rng_xor128_u32(rng_xor128_state);
	char secret[5];curd_pick(secret);

	int8_t hint[5*6];int gn=do_curd(secret,hint);

	print(NL NL " Curdle ");printi(curd);printc(' ');
	printi(gn);print("/6" NL NL);

	for(int g=0;g<gn;++g){
		printc(' ');
		for(int i=0;i<5;++i){
			term_nocolor();
			printc(' ');
			int h=hint[g*5+i];
			hint_style(h);
			print("  ");
		}
		term_nocolor();
		print(NL NL);
	}
}

static void do_freeplay(){
	print(NL "Free Play Mode" NL);
	long time=time_msec();//printl(time);print(NL);
	rng_xor128_state[3]^=~(uint32_t)time_msec();
	char secret[5];
	//for(int i=0;i<10;++i){curd_pick(secret);}
	while(1){print(NL);curd_pick(secret);int8_t h[5*6];do_curd(secret,h);}}

int main(){print(banner);do_daily();do_freeplay();}
