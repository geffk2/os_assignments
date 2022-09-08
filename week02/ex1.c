#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void)
{
  int a1 = INT_MAX; 
  printf("%d %zu\n", a1, sizeof(a1));
      
  unsigned short int a2 = USHRT_MAX;
  printf("%d %zu\n", a2, sizeof(a2));

  long int a3 = LONG_MAX;
  printf("%ld %zu\n", a3, sizeof(a3));


  float a4 = FLT_MAX;
  printf("%f %zu\n", a4, sizeof(a4));


  double a5 = DBL_MAX;
  printf("%f %zu\n", a5, sizeof(a5));

  return 0;
}

