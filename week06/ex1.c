#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _job_t {
  int id;
  int arrival, burst;
  int completion, turnaround, waiting;
} job_t;

int compare(const void* _a, const void* _b) {
  job_t* a = (job_t*)_a;
  job_t* b = (job_t*)_b;

  return (a->arrival > b->arrival) - (a->arrival < b->arrival);
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
    jobs[i].id = i;
  }
  qsort(jobs, n, sizeof(job_t), &compare);
  int clock = 0;
  int tat_sum = 0, wt_sum = 0;

  for(int i = 0; i < n; i++) {
    job_t j = jobs[i];
    j.waiting = clock - j.arrival;
    j.turnaround = j.burst + j.waiting;
    j.completion = j.arrival + j.turnaround;
    printf("Process %d:\nCT:%d\tTAT:%d\tWT:%d\n", j.id, j.completion, j.turnaround, j.waiting);

    wt_sum += j.waiting;   
    tat_sum += j.turnaround;

    clock = j.completion;
  }
  printf("Avg WT: %lf\nAvg TAT: %lf\n", (double)wt_sum / n, (double)tat_sum / n);

  return 0;
}
