#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>

int main (int argc, char *argv[])
{
  char* arr[10];
  struct rusage usage;
  for(int i = 0; i < 10; i++) {
    arr[i] = malloc(10 * 1024 * 1024);
    memset(arr[i], 0, 10 * 1024 * 1024); 

    if(getrusage(RUSAGE_SELF, &usage) == 0)
      printf("%ld\n", usage.ru_maxrss);

    sleep(1);
  }

  for(int i = 0; i < 10; i++) {
    free(arr[i]);
  }

  return 0;
}
