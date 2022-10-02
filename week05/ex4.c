#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define true 1
#define false 0

int result = 0;
pthread_mutex_t mut;

int is_prime(int n) {
  if (n <= 1)
    return 0;
  for (int d = 2; d * d <= n; d++)
    if (n % d == 0)
      return 0;
  return 1;
}

int primes_count_in_interval(int start, int finish) {
  int ret = 0;
  for (int i = start; i < finish; i++)
    if (is_prime(i) != 0)
      ret++;
  return ret;
}

typedef struct prime_counter_request
{
  int start, finish;
} Req;

void* thread(void* arg) {
  Req* req = (Req*) arg;
  int cnt = primes_count_in_interval(req->start, req->finish);
  free(req);
  pthread_mutex_lock(&mut);
  result += cnt;
  pthread_mutex_unlock(&mut);

  return NULL;
}

int main(int argc, char *argv[]) {
  if(argc < 2) {
    return 1;
  }
  int n, m;
  sscanf(argv[1], "%d", &n);
  sscanf(argv[2], "%d", &m);
  int per_process = n / m;
  pthread_t* threads = calloc(m, sizeof(pthread_t)); 

  pthread_mutex_init(&mut, NULL);
  for(int i = 0; i < m; i++) {
    int start = i * per_process;
    int end = i + 1 < m ? (i + 1) * per_process : n; 

    Req* req = malloc(sizeof(Req));
    req->start = start;
    req->finish = end;

    pthread_create(threads + i, NULL, &thread, req);
  }

  for(int i = 0; i < m; i++) {
    pthread_join(threads[i], NULL);
  }
  printf("%d\n", result);

  free(threads);
  pthread_mutex_destroy(&mut);
  return 0;
}
