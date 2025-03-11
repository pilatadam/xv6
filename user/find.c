#include "find.h"

int
main(int argc, char* argv[])
{

    exit(0);
}

void
find(struct dirent de, char *needle)
{
    int fd;
    struct dirent de;
    struct stat st;

    // if((fd = open(path, O_RDONLY)) < 0){
    //     fprintf(2, "find: cannot open %s\n", path);
    //     return;
    // }
    //
    // if(fstat(fd, &st) < 0){
    //   fprintf(2, "ls: cannot stat %s\n", path);
    //   close(fd);
    //   return;
    // }
}

int
is_valid_dir(char *path)
{
  return strcmp(path, ".") != 0 && strcmp(path, "..") != 0;
}
