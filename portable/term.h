#define DOS_USE_GRAPH
#include "print.h"
#undef DOS_USE_GRAPH

#if !defined(__MINT__) && !defined(__WATCOMC__) // posix?
// ANSI
#define BLACK  30
#define GREEN  32
#define YELLOW 33
#define WHITE  37
#define BR_BLACK 90
#define BR_WHITE 97
SHL void term_ansicolor(int c){
	print("\33[");
	printi(c);
	printc('m');
}
#define term_nocolor()  term_ansicolor(0)
#define term_fgcolor(c) term_ansicolor(c)
#define term_bgcolor(c) term_ansicolor(c+10)
#define term_inverse()  term_ansicolor(7)
#define term_normal()   term_ansicolor(27)
#endif

#ifdef __MINT__ // GEMDOS VT52
#define BLACK 0
#define YELLOW 1
#define GREEN 2
#define WHITE 15
#define BR_BLACK 0
#define BR_WHITE 15
SHL void term_fgcolor(int c){
	print("\33b");
	printc(' '+c);
}
SHL void term_bgcolor(int c){
	print("\33c");
	printc(' '+c);
}
SHL void term_nocolor(){
	term_fgcolor(WHITE);
	term_bgcolor(BLACK);
}
#endif

#ifdef __WATCOMC__ // MS-DOS
#define BLACK   0
#define BLUE    1
#define GREEN   2
#define CYAN    3
#define RED     4
#define MAGENTA 5
#define YELLOW  6
#define WHITE   7
#define BR_BLACK   8
#define BR_BLUE    9
#define BR_GREEN   10
#define BR_CYAN    11
#define BR_RED     12
#define BR_MAGENTA 13
#define BR_YELLOW  14
#define BR_WHITE   15
SHL void term_nocolor(void){_settextcolor(WHITE);_setbkcolor(BLACK);}
SHL void term_fgcolor(int c){_settextcolor(c);}
SHL void term_bgcolor(int c){_setbkcolor(c);}
#endif
