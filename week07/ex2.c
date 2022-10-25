#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int n;
  printf("Enter N: ");
  scanf("%d", &n);

  int *arr = calloc(n, sizeof(int));
  for(int i = 0; i < n; i++) {
    arr[i] = i;
  }
  
  for(int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }

  free(arr);

  return 0;
}
