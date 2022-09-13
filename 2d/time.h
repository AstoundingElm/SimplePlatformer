#pragma once

#include "types.h"

#if _POSIX_C_SOURCE >= 199309L
#include <time.h>  // nanosleep
#else
#include <unistd.h>  // usleep
#endif

struct clock_types{
    
    f64 start_time;
    f64 elapsed;
};
static clock_types  clock_context;

void platform_sleep(u64 ms) {
#if _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000 * 1000;
    nanosleep(&ts, 0);
#else
    if (ms >= 1000) {
        sleep(ms / 1000);
    }
    usleep((ms % 1000) * 1000);
#endif
}

f64 platform_get_absolute_time() {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_sec + now.tv_nsec * 0.000000001;
}

void clock_update(clock_types * clock){
    
    if(clock->start_time != 0){
        
        clock->elapsed = platform_get_absolute_time() - clock->start_time;}
};

void clock_start(clock_types * clock){
    
    clock->start_time = platform_get_absolute_time();
    clock->elapsed = 0;
};

void clock_stop(clock_types * clock){
    
    clock->start_time = 0;};

