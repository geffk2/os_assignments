#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include<sys/stat.h>
#include<sys/types.h>
int main(int argc, char* argv[])
{
  if(argc < 1) {
    return 1;
  }
  int n;
  if(sscanf(argv[1], "%d", &n) == 0) {
    return 1;
  }

  // publisher
  mkfifo("/tmp/ex2", 0777);

  printf("Publisher Opening\n");
  int fd = open("/tmp/ex2", O_WRONLY);
  if(fd == -1) {
    return 3;
  }
  printf("Publisher Open\nTo stop sending messages type exit\n");

  char* buf = NULL;
  size_t bufsize;
  for(;;) {
    getline(&buf, &bufsize, stdin);
    if(strcmp(buf, "exit\n") == 0) {
      break;
    }
    char message[1024];
    strncpy(message, buf, 1023);
    free(buf);
    buf = NULL;

    if(fork() == 0) {
      sleep(1);
      for(int i = 0; i < n; i++) {
        write(fd, message, 1024);
      }
      return 0;
    }
  }

  printf("Publisher closing\n");
  close(fd);
  return 0;
}

