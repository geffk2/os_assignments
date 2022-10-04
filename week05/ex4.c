#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int result = 0;
int nextNumber = 0;

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

int is_prime(int n) {
  if (n <= 1)
    return 0;
  for (int d = 2; d * d <= n; d++)
    if (n % d == 0)
      return 0;
  return 1;
}


void* thread(void* arg) {
  int* lim = (int*) arg;
  int cnt = 0;
  int currentNum;

  for(;;) {
    pthread_mutex_lock(&mut);
    currentNum = nextNumber++;
    pthread_mutex_unlock(&mut);
    if(currentNum >= *lim) {
      break;
    }
    cnt += is_prime(currentNum);
  }

  pthread_mutex_lock(&mut);
  result += cnt;
  pthread_mutex_unlock(&mut);

  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  if(argc < 2) {
    return 1;
  }
  int n, m;
  sscanf(argv[1], "%d", &n);
  sscanf(argv[2], "%d", &m);
  pthread_t* threads = calloc(m, sizeof(pthread_t)); 

  for(int i = 0; i < m; i++) {
    pthread_create(threads + i, NULL, &thread, &n);
  }

  for(int i = 0; i < m; i++) {
    pthread_join(threads[i], NULL);
  }
  printf("%d\n", result);

  free(threads);

  pthread_mutex_destroy(&mut);
  return 0;
}
