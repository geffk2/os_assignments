#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_SIZE 1024
#define PATH_SIZE 2048
#define NAME_SIZE 64

struct Directory;
struct File;

struct File {
  char id;
  char name[NAME_SIZE];
  size_t size;
  char data[DATA_SIZE];
  struct Directory* dir;
};

struct Directory {
  int nf, nd;
  char name[NAME_SIZE];
  struct File* files[256];
  struct Directory* directories[8];
  struct Directory* parent;
  char path[PATH_SIZE];
};

typedef struct File File;
typedef struct Directory Directory;

void add_to_file(File* f, const char* str) {
  strcpy(f->data, str);
}

void append_fo_file(File* f, const char* str) {
  strncat(f->data, str, DATA_SIZE - f->size);
}

void pwd_file(File* f) {
  char path[2048];  
  strcpy(path, f->dir->path);
  strncat(path, f->name, PATH_SIZE - f->size);
  printf("%s\n", path);
}

void add_file(File* f, Directory* dir) {
  if(dir->nf < 256) {
    dir->files[dir->nf++] = f;
    f->dir = dir;
  } 
}

void add_dir(Directory* child, Directory* parent) {
  if(parent->nd < 8) {
    parent->directories[parent->nd++] = child;
    child->parent = parent;
    strcpy(child->path, parent->path);
    strncat(child->path, child->name, PATH_SIZE - strlen(child->path));
    strncat(child->path, "/", PATH_SIZE - strlen(child->path));
  } 
}

Directory* create_dir(const char* name) {
  Directory* res = malloc(sizeof(Directory));
  *res = (Directory){ .nf = 0, .nd = 0 };
  strncpy(res->name, name, 64);
  strncpy(res->path, name, PATH_SIZE);
  strncpy(res->path, "/", PATH_SIZE - strlen(name));
  return res;
}

File* create_file(char id, const char* name, const char* content) {
  File* res = malloc(sizeof(File));
  *res = (File){.id = id};
  strncpy(res->name, name, NAME_SIZE);
  strncpy(res->data, content, DATA_SIZE);
  res->size = strlen(res->data);
  return res;
}

int main(int argc, char* argv[])
{
  Directory* root = create_dir("/");
  Directory* home = create_dir("home");
  Directory* bin = create_dir("bin");
  add_dir(home, root);
  add_dir(bin, root);

  File* bash = create_file(0, "bash", "");
  add_file(bash, bin);

  File* ex31 = create_file(1, "ex3_1.c", "int printf(const char * format, ...);");
  File* ex32 = create_file(2, "ex3_2.c", "//This is a comment in C language");
  add_file(ex31, home);
  add_file(ex32, home);

  add_to_file(bash, "Bourne Again Shell!!");

  pwd_file(bash);
  pwd_file(ex31);
  pwd_file(ex32);

  free(root);
  free(home);
  free(bin);
  free(bash);
  free(ex31);
  free(ex32);
  return 0;
}
