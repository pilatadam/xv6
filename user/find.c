#include "find.h"

int
main(int argc, char* argv[])
{
    find(argv[1], argv[2]);
    exit(0);
}

void
find(char *path, char *needle)
{
    int fd;
    struct dirent de;
    struct stat st;
    char buf[512], *p;

    if((fd = open(path, O_RDONLY)) < 0){
      fprintf(2, "ls: cannot open %s\n", path);
      return;
    }

    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';

    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      
      if(strcmp(needle, de.name) == 0)
        printf("%s\n", buf);
     
       if(stat(buf, &st) < 0){
         printf("ls: cannot stat %s\n", buf);
         continue;
       }
      
       switch(st.type){
         case T_DIR:
           if(is_valid_dir(de.name))
             find(buf, needle); 
         default:
           break;
       }
    }

    close(fd);
}

int
is_valid_dir(char *name)
{
    return strcmp(name, ".") != 0 && strcmp(name, "..") != 0;
}
