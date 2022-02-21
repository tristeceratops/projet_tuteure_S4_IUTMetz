#ifndef CPU_TIME
#define CPU_TIME

#include <time.h>

void clock_start(clock_t *t);
void clock_end(clock_t *t);
void print_clock(clock_t t1, clock_t t2);

#endif