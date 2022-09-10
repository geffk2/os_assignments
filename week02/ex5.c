#include <stdio.h>

unsigned long long int tribonacci(int n) {
  int t0 = 0, t1 = 1, t2 = 1;
  switch(n) {
    case 0:
      return 0;
    case 1:
    case 2:
      return 1;
  }
  for(int i = 0; i < n - 3; i++) {
    int buf = t2;
    t2 += t0 + t1;
    t0 = t1;
    t1 = buf;
  }


  return t0 + t1 + t2;
}

int main(int argc, char* argv[]) {
  printf("T4 = %llu\nT36 = %llu\n", tribonacci(4), tribonacci(36));
  return 0;
}
