#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), 0, DIRSIZ-strlen(p));
  return buf;
}

void
find(char *path, char *target)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  fd = open(path, 0);
  fstat(fd, &st);
  strcpy(buf, path);
  p = buf+strlen(buf);
  *p++ = '/';
  while(read(fd, &de, sizeof(de)) == sizeof(de)){
    if(de.inum == 0)
      continue;
    memmove(p, de.name, DIRSIZ);
    p[DIRSIZ] = 0;
    stat(buf, &st);

    if(st.type == T_DIR && (strcmp(".",fmtname(buf)) != 0 && strcmp("..",fmtname(buf)) != 0) ) {
      find(buf, target);
    }else if(st.type == T_FILE && strcmp(target,fmtname(buf)) == 0 ) {
      printf("%s\n", buf);

    }

  }
  
  
  close(fd);
}

int
main(int argc, char *argv[])
{

  if(argc != 3){
    fprintf(2, "find args err\n");
    exit(1);
  }
  printf("begin\n");
  find(argv[1],argv[2]);
  exit(0);
}
