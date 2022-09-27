#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

#define VEC_LENGTH 120

int main(int argc, char* argv[])
{
  srand((unsigned) time(NULL));
  int u[VEC_LENGTH], v[VEC_LENGTH];
  for(int i = 0; i < VEC_LENGTH; i++) {
    u[i] = rand() % 100;
    v[i] = rand() % 100;
  }
  
  int n;
  printf("Enter number of processes: ");
  scanf("%d", &n);

  FILE* tmp = fopen("temp.txt", "w"); // erase previous file contents
  fclose(tmp);

  int i = 0;
  int pid = -1;
  for(; i < n; i++) {
    pid = fork();
    if(pid == 0) {
      break; // each child process get its own unique i
    }
  } 

  if(pid != 0) {
    wait(NULL); // parent waits for all children to finish, reads and adds up results;
    FILE* temp = fopen("temp.txt", "r");
    long long int res = 0;
    for(int j = 0; j < n; j++) {
      long long int buf;
      fscanf(temp, "%lld", &buf);
      res += buf;
    }
    fclose(temp);
    printf("Result: %lld\n", res);
  } else {
    FILE* temp = fopen("temp.txt", "a"); // children calculate result, write it to file and call it a day
    long long res = 0;
    for(; i < VEC_LENGTH; i += n) {
      res += u[i] * v[i];
    }

    fprintf(temp, "%lld\n", res);
    fflush(temp);
    fclose(temp);
  }

  return 0;
}

