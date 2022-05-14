#define DOS_USE_GRAPH
#include "print.h"
#undef DOS_USE_GRAPH

#ifndef __WATCOMC__
#ifndef __MINT__ // ANSI
SHL void term_bgcolor(int c){
	print("\33[4");
	printc('0'+c);
	printc('m');
}
#else // VT52
SHL void term_bgcolor(int c){
	print("\33c");
	printc(c);
}
#endif
#else // MS-DOS
SHL void term_bgcolor(int c){_setbkcolor(c);}
#endif
