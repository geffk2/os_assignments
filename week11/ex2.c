#include <dirent.h>
#include <stdio.h>

int main() {
  DIR *pwd = opendir(".");
  struct dirent* dp; 

  while((dp = readdir(pwd)) != NULL) {
    printf("%s\n", dp->d_name);
  }

  closedir(pwd);
}
