#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_prompt() {
  system("pwd");
  printf(" > ");
}

int main(int argc, char* argv[]) {

  char* buf = NULL;
  size_t linecap = 0;

  for(;;) {
    print_prompt();
    getline(&buf, &linecap, stdin);
    system(buf);
  }
  return 0;
}

