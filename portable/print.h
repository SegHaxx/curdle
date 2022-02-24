#include <stdint.h>
#include <stdbool.h>

#ifdef __GNUC__ // shut up gcc
#define SHL static __attribute__((__unused__))
#else
#define SHL static
#endif

#if !defined(__MINT__) && !defined(__WATCOMC__) // unix?
	#include <stdio.h>
	#define NL "\n"
	#define print(s) fputs(s,stdout)
	#define printc(c) fputc(c,stdout)
	#define print_flush() fflush(stdout)
	#define pause_if_gui() {};
#endif

#ifdef __MINT__ // Atari ST TOS
	#include <osbind.h>
	#define NL "\r\n"
	#define print(s) Cconws(s)
	#define printc(c) Cconout(c)
	#define print_flush() {}
	#define pause_if_gui() Cconin();
#endif

#ifdef __WATCOMC__ // MS-DOS
	#include <conio.h>
	#define NL "\r\n"
	#define print(s) cputs(s);
	#define printc(c) putch(c);
	#define print_flush() {}
	#define pause_if_gui() {}
#endif

SHL void div10_rem_u16(uint16_t n, uint16_t* qp, uint16_t* rp){
	uint16_t q,r;
	q = (n >> 1) + (n >> 2);
	q = q + (q >> 4);
	q = q + (q >> 8);
	q = q >> 3;
	r = n - (((q << 2) + q) << 1);
	if(r>9){
		q+=1;
		r-=10;
	}
	*qp = q;
	*rp = r;
}

SHL void print_u16(uint16_t n){
	char tmp[6];
	char* str=tmp+5;
	*str = 0;
	do{
#if 0
		*--str = '0'+(n%10);
		n /= 10;
#else
		uint16_t q,r;
		div10_rem_u16(n, &q, &r);
		*--str = '0'+r;
		n = q;
#endif
	} while (n > 0);
	print(str);
}

SHL void div10_rem_u32(uint32_t n, uint32_t* qp, uint32_t* rp){
	uint32_t q,r;
	q = (n >> 1) + (n >> 2);
	q = q + (q >> 4);
	q = q + (q >> 8);
	q = q + (q >> 16);
	q = q >> 3;
	r = n - (((q << 2) + q) << 1);
	if(r>9){
		q+=1;
		r-=10;
	}
	*qp = q;
	*rp = r;
}

SHL void print_u32(uint32_t n){
	char tmp[11];
	char* str=tmp+10;
	*str = 0;
	do{
#if 1
		*--str = '0'+(n%10);
		n /= 10;
#else
		uint16_t q,r;
		div10_rem_u32(n, &q, &r);
		*--str = '0'+r;
		n = q;
#endif
	} while (n > 0);
	print(str);
}
