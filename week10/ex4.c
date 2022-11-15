#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char *argv[])
{
  DIR *tmpdir = opendir("tmp"); 
  struct dirent* dp;

  printf("File \t Hard Links\n");
  while((dp = readdir(tmpdir)) != NULL) {
    struct stat res;
    fstatat(dirfd(tmpdir), dp->d_name, &res, AT_SYMLINK_NOFOLLOW);

    if(res.st_nlink > 1) {
      DIR *dir1 = opendir("tmp");
      struct dirent* dp1;
      printf("%s \t ", dp->d_name);

      while((dp1 = readdir(dir1)) != NULL) {
        if(dp1->d_ino == dp->d_ino) {
          printf("%s ", dp1->d_name);
        }
      }
      closedir(dir1);
      printf("\n");
    }
  }
  closedir(tmpdir);
  
  return 0;
}
