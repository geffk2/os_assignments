#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
  if(argc < 1) {
    return EXIT_SUCCESS;
  }
  long int n;

  n = strtol(argv[1], NULL, 10);
  for(int i = 0; i < n; i++) {
    fork();
    sleep(5);
  }
  wait(NULL);

  return EXIT_SUCCESS;
}

