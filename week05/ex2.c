#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <pthread.h>

#define true 1
#define false 0

typedef struct Thread {
  int i;
  pthread_t id;
  char message[256];
} Thread;

void* func(void* arg) {
  Thread* info = (Thread*) arg; 
  printf("%zd %s\n", info->id, info->message); // assuming pthread_t is size_t. Not happy about it.

  return NULL;
}

int main(int argc, char *argv[]) {
  int n;
  printf("Input number of threads to create: ");
  scanf("%d", &n);

  Thread* threads = calloc(n, sizeof(Thread));
  for(int i = 0; i < n; i++) {
    threads[i].i = i; 
    sprintf(threads[i].message, "Hello from thread %d", i);
    pthread_create(&threads[i].id, NULL, &func, threads + i);
    printf("Thread %d is created\n", i);
    pthread_join(threads[i].id, NULL);
  }
  return 0;
}
