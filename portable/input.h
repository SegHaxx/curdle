#ifdef __MINT__ // Atari ST TOS
	#include <osbind.h>
	typedef _CCONLINE INPUT_T;
	#define input(b) Cconrs(b)
#else

typedef struct{
	uint8_t maxlen;
	uint8_t actuallen;
	char    buffer[255];
} INPUT_T;

#ifdef __WATCOMC__ // MS-DOS
#include <conio.h>
SHL void input(INPUT_T* buf){
	++buf->maxlen; // why?
	cgets((char*)buf);
	--buf->maxlen;}

#else // unix?
#include <stdio.h>
SHL void input(INPUT_T* buf){
	fgets(buf->buffer,255,stdin);
	int i=0;
	for(;i<(int)buf->maxlen;++i){
		if(buf->buffer[i]==0) break;}
	buf->actuallen=i;
	print("\33M");}
#endif
#endif
