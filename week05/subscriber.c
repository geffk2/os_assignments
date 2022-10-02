#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>
int main(int argc, char* argv[])
{
  // subscriber
  
  printf("Subscriber Opening\n");
  int fd = open("/tmp/ex2", O_RDONLY);
  if(fd == -1) {
    printf("Pipe does not exist\n");
    return 3;
  }

  char buf[1024];
  for(;;) {
    ssize_t res = read(fd, buf, 1024);
    if(res == 0) {
      break;
    }
    printf(">%s", buf);
    fflush(stdout);
    sleep(1);
  }
  close(fd);
  return 0;
}
