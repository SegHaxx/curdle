#if !defined(__MINT__) && !defined(__WATCOMC__) // posix?
#if 0
#include <sys/time.h>
SHL long time_msec(void){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}
#else
#include <time.h>
SHL long time_msec(void){
    struct timespec tv;
    clock_gettime(CLOCK_MONOTONIC_COARSE,&tv);
    return (((long)tv.tv_sec)*1000)+(tv.tv_nsec/1000000);
}
#endif
#endif

#ifdef __MINT__
#include <mint/sysvars.h>
SHL long get_hz_200(void){return *(_hz_200);}
SHL long time_msec(void){return 20*Supexec(get_hz_200);}
#endif

#ifdef __WATCOMC__
#include <time.h>
SHL long time_msec(void){
	return clock()/(CLOCKS_PER_SEC/1000);
}
#endif
