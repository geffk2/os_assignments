#include <stdio.h>

int main(void)
{
  char s[256];

  int i;
  for(i = 0; i < 256; i++) {
    s[i] = getchar();
    if(s[i] == '.' || s[i] == '\n') {
      break;
    }
  }

  printf("\"");
  for(; i >= 0; i--) {
    printf("%c", s[i]);
  }
  printf("\"\n");

  return 0;
}
