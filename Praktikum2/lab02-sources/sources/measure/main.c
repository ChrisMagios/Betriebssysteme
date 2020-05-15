#include "measure.h"

#define TRACEPOINT_DEFINE
#include "tp.h"

#include <stdlib.h>

int main(int argc, char* argv[]) {
  int mycounter = rand();
  getchar();
  measure_start();
  tracepoint(my_trace, counter, mycounter);
  measure_end();
  measure_print();

  return 0;
}
