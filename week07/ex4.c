#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h> 

void* _realloc(void* ptr, int new_size) {

  void* res = malloc(new_size);
  if(ptr == NULL) {
    return res;
  }
  int old_size = malloc_usable_size(ptr);

  memcpy(res, ptr, old_size < new_size ? old_size : new_size);
  free(ptr);
  return res;
}

int main(int argc, char *argv[]) {
  int n, m;
  scanf("%d", &n);
  int *arr = calloc(n, sizeof(int));
  for(int i = 0; i < n; i++) {
    arr[i] = i;
  }
  scanf("%d", &m);
  arr = realloc(arr, m * sizeof(int)); 

  for(int i = 0; i < m; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  return 0;
}

