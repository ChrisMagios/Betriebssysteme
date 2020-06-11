#pragma once

#include <stdio.h>
#include <time.h>

__thread struct timespec tstart, tend;

static inline void measure_start() {
  clock_gettime(CLOCK_MONOTONIC, &tstart);
}

static inline void measure_end() {
  clock_gettime(CLOCK_MONOTONIC, &tend);
}

static inline void measure_print() {
  printf("measured %.9f seconds\n",
           ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) -
           ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));
}
