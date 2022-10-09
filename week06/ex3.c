#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <sys/wait.h>

typedef struct _job_t {
  int id;
  int arrival, burst;
  int completion, turnaround, waiting;
  int last_burst;
} job_t;

typedef struct _queue_t {
  job_t **base;
  int size, head, tail, len;
} queue_t;

void new_queue(queue_t* q, int size) {
  q->size = size;
  q->len = 0;
  q->base = calloc(size, sizeof(job_t*));
  q->head = 0;
  q->tail = 0;
}

void q_push(queue_t* q, job_t* el) {
  q->base[q->head] = el;
  q->head = (q->head + 1) % q->size;
  q->len++;
}

void q_pop(queue_t* q) {
  q->tail = (q->tail + 1) % q->size;
  q->len--;
}

job_t* q_peek(queue_t* q) {
  if(q->head == q->tail) {
    return NULL;
  }
  return q->base[q->tail];
}

int q_empty(queue_t* q) {
  return q->len == 0;
}

int compareArrival(const void* _a, const void* _b) {
  job_t* a = (job_t*)_a;
  job_t* b = (job_t*)_b;

  return (a->arrival > b->arrival) - (a->arrival < b->arrival);
}

int countFitting(int clock, job_t* jobs, size_t n) {
  int i = 0;
  for(int j = 0; j < n; j++) {
    if(jobs[j].arrival <= clock) {
      i++;
    } else {
      return i;
    }
  }
  return i;
}


int main(int argc, char *argv[]) {
  int n, quantum;
  printf("Enter number of processes: ");
  scanf("%d", &n);
  printf("Enter quantum length: ");
  scanf("%d", &quantum);
  job_t* jobs = calloc(n, sizeof(job_t));
  printf("Enter process arrival times:\n");

  for(int i = 0; i < n; i++) {
    scanf("%d", &(jobs[i].arrival));
    jobs[i].last_burst = jobs[i].arrival;
    jobs[i].completion = 0;
    jobs[i].turnaround = 0;
    jobs[i].waiting = 0;
    jobs[i].id = i + 1;
  }
  printf("Enter process burst times:\n");
  for(int i = 0; i < n; i++) {
    scanf("%d", &(jobs[i].burst));
  }

  qsort(jobs, n, sizeof(job_t), &compareArrival);
  int clock = jobs->arrival;
  int tat_sum = 0, wt_sum = 0;
  queue_t qu;
  new_queue(&qu, n);

  for(int i = 0; i < n || !q_empty(&qu);) {
    // add new jobs to queue 
    for(; jobs[i].arrival <= clock && i < n; i++) {
      q_push(&qu, jobs + i); 
    }
    // process current job 
    if(q_empty(&qu)) {
      // queue is empty, skip to next job's Arrival
      // the loop is still running so there are some jobs yet to arrive
      clock = jobs[i].arrival;
      continue;
    }
    job_t* j = q_peek(&qu);
    j->waiting += clock - j->last_burst;

    int timeskip = j->burst < quantum ? j->burst : quantum;
    clock += timeskip;
    j->burst -= timeskip;
    q_pop(&qu); 

    // add new jobs to queue 
    for(; jobs[i].arrival <= clock && i < n; i++) {
      q_push(&qu, jobs + i); 
    }

    if(j->burst > 0) {
      q_push(&qu, j);
      continue;
    }
    // job is done

    j->turnaround = clock - j->arrival;
    j->completion = clock;
    printf("Process %d:\nCT:%d\tTAT:%d\tWT:%d\n", j->id, j->completion, j->turnaround, j->waiting);

    wt_sum += j->waiting;   
    tat_sum += j->turnaround;
  }
  printf("Avg WT: %lf\nAvg TAT: %lf\n", (double)wt_sum / n, (double)tat_sum / n);

  free(qu.base);
  free(jobs);
  return 0;
}
