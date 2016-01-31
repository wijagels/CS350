#include "mytimer.h"

static suseconds_t start;
static struct timeval tv;

void settimer() {
    gettimeofday(&tv, 0);
    start = tv.tv_usec;
}

suseconds_t endtimer() {
    gettimeofday(&tv, 0);
    suseconds_t end = tv.tv_usec;
    return end - start;
}
