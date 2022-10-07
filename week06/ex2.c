#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

typedef struct _job_t {
  int id;
  int arrival, burst;
  int completion, turnaround, waiting;
} job_t;

int compareArrival(const void* _a, const void* _b) {
  job_t* a = (job_t*)_a;
  job_t* b = (job_t*)_b;

  return (a->arrival > b->arrival) - (a->arrival < b->arrival);
}

int compareBurst(const void* _a, const void* _b) {
  job_t* a = (job_t*)_a;
  job_t* b = (job_t*)_b;

  return (a->burst > b->burst) - (a->burst < b->burst);
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
  int n;
  printf("Enter number of processes: ");
  scanf("%d", &n);
  job_t* jobs = calloc(n, sizeof(job_t));

  for(int i = 0; i < n; i++) {
    printf("Process %d:\n", i + 1);
    printf("Arrival time: ");
    scanf("%d", &(jobs[i].arrival));
    printf("Burst time: ");
    scanf("%d", &(jobs[i].burst));
    jobs[i].completion = 0;
    jobs[i].turnaround = 0;
    jobs[i].waiting = 0;
    jobs[i].id = i + 1;
  }
  qsort(jobs, n, sizeof(job_t), &compareArrival);
  int clock = jobs->arrival;
  int tat_sum = 0, wt_sum = 0;

  for(int i = 0; i < n; i++) {
    qsort(jobs + i, n - i, sizeof(job_t), &compareArrival);
    int m = countFitting(clock, jobs + i, n - i);
    qsort(jobs + i, m, sizeof(job_t), &compareBurst);
    job_t* j = jobs + i;
  
    j->waiting = clock - j->arrival;
    j->turnaround = j->burst + j->waiting;
    j->completion = j->arrival + j->turnaround;
    printf("Process %d:\nCT:%d\tTAT:%d\tWT:%d\n", j->id, j->completion, j->turnaround, j->waiting);

    wt_sum += j->waiting;   
    tat_sum += j->turnaround;

    clock = j->completion;
  }
  printf("Avg WT: %lf\nAvg TAT: %lf\n", (double)wt_sum / n, (double)tat_sum / n);

  free(jobs);
  return 0;
}
