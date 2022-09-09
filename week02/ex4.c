#include <stdio.h>
#include <ctype.h>

unsigned long int count(char* str, char target) {
  target = tolower(target);
  unsigned long res = 0;
  for(; *str != '\0'; str++) {
    if(tolower(*str) == target) {
      res++;
    }
  }
  return res;
}

void countAll(char* str) {
  char* strPtr = str;
  for(; *strPtr != '\0'; strPtr++) {
    printf("%c:%lu, ", *strPtr, count(str, *strPtr));
  }
  printf("\n");
}

int main(int argc, char* argv[]) {
  char str[256];
  scanf("%s", str);
  countAll(str);
  return 0;
}
