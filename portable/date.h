#if !defined(__MINT__) && !defined(__WATCOMC__)
#include <stdio.h>
#include <time.h>
SHL void get_date(int* y,int* m,int* d){
	time_t t=time(NULL);
	struct tm* date=localtime(&t);
	*y=date->tm_year+1900;
	*m=date->tm_mon+1;
	*d=date->tm_mday;
}
#endif

#ifdef __MINT__
SHL void get_date(int* y,int* m,int* d){
	uint32_t date=Tgetdate();
	*y=(0x7f&date>>9)+1980;
	*m=0x0f&date>>5;
	*d=0x1f&date;
}
#endif

#ifdef __WATCOMC__
#include <dos.h>
SHL void get_date(int* y,int* m,int* d){
	struct dosdate_t date;
	_dos_getdate(&date);
	*y=date.year;
	*m=date.month;
	*d=date.day;
}
#endif
