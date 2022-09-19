#include <stdio.h>
#include <stdlib.h>

int foo(int age) {
  return 2022 - age;
}

int main(int argc, char* argv[])
{
  const int x = 10;
  const int* q = &x;
  const int *const p = malloc(sizeof(int) * 5);

  for(int i = 0; i < 5; i++) {
    int* tmp = p + i;
    *tmp = x;
    printf("%d ", p[i]);
  }
  printf("\nInput ages:");
  scanf("%d %d %d %d %d", p, p+1, p+2, p+3, p+4);

  for(int i = 0; i < 5; i++) {
    int* tmp = p + i;
    *tmp = foo(p[i]);
  }

  free(p);
  return 0;
}

