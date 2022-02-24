#include "print.h" // we need to override some stuff on MS-DOS

#ifndef __WATCOMC__
SHL void term_bgcolor(int c){
#ifndef __MINT__ // ANSI
	print("\33[4");
	printc('0'+c);
	printc('m');
#else // VT52
	print("\33c");
	printc(c);
#endif
}
#else // MS-DOS
#include <graph.h>
#undef print
#undef printc
#define print(s) _outtext(s)
SHL void printc(char c){_outmem(&c,1);}
SHL void term_bgcolor(int c){_setbkcolor(c);}
#endif
