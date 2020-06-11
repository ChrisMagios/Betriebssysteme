#include <stdio.h>

extern int A[];

int main() {
  int x = 0 ;

  for ( int i = 0 ; i < 10000 ; i ++) {
    x += A[i] ;
  }

  printf("%d\n", x);
}
