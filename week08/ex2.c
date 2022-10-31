#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[])
{
  char* arr[10];
  for(int i = 0; i < 10; i++) {
    arr[i] = malloc(10 * 1024 * 1024);
    memset(arr[i], 0, 10 * 1024 * 1024); 
    // after this line is executed(checked with lldb), value in "free" column drops by approx. 10200
    // "si" and "so" fields stay at zero at all times(tested on a VM)
    // in "top -i 1 -o mem" MEM value for this process incerases by 10M. it steadily climbs the chart before stopping completely  
    sleep(1);
  }
  for(int i = 0; i < 10; i++) {
    free(arr[i]);
  }

  return 0;
}
