#include <stdio.h>
#include <math.h>
#include <strings.h>

void convert(long long int src, int from, int to) {
  char str[20];
  sprintf(str, "%lld", src);
  int decimal = 0;
  long int power = 1;
  if(from < 2 || from > 10 || to < 2 || to > 10) {
    printf("Invalid numeral base.\n");
    return;
  }

  for(int i = strlen(str) - 1; i >= 0; i--) {
    int digit = str[i] - '0';

    if(digit >= from) {
      printf("Incorrect number.\n");
      return;
    }
    decimal += digit * power; 
    power *= from;
  }
  long long int res = 0;
  power = 1;
  while(decimal >= 1) {
    int rem = decimal % to;
    decimal /= to;
    res += rem * power;
    power *= 10;
  }
  printf("%lld\n", res);

}

int main(int argc, char* argv[])
{
  long long src;
  int from, to;
  printf("Input number to convert, source and target numeral systems:\n");
  scanf("%lld %d %d", &src, &from, &to);
  convert(src, from, to);

  return 0;
}
