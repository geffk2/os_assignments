#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  int fd[2];
  pipe(fd);

  if(fork() != 0) { // publisher
    char* message = NULL;
    size_t bufsize;

    getline(&message, &bufsize, stdin);

    write(fd[1], &bufsize, sizeof(size_t));
    write(fd[1], message, bufsize);

    free(message);
  } else { // subscriber
    char* message;
    size_t len;

    read(fd[0], &len, sizeof(size_t));

    message = malloc(len);
    read(fd[0], message, len);
    printf("%s", message);

    free(message);
  }

  close(fd[0]);
  close(fd[1]);
  wait(NULL);
  return 0;
}

