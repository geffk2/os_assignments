#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
  int pid1 = fork();
  if(pid1 != 0) {
    fork();
  }
  time_t t1 = clock();
  int pid = getpid();
  printf("PID: %d PPID: %d\n", pid, getppid());
  time_t t2 = clock();
  printf("PID: %d Time: %ld\n", pid, t2 - t1); // c11
  wait(NULL);

  return 0;
}

