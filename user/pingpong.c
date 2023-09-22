#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int p[2];

  if(argc != 1){
    fprintf(2, "Usage: pingpong err\n");
    exit(1);
  }
  
  pipe(p);

  int pid = fork();
  if(pid > 0){
    write(p[1], "\n", 1);
    close(p[1]);
    wait((int *) 0);
    fprintf(1, "%d: received pong\n", getpid());
    close(p[0]);
    close(p[1]);
  } else if(pid == 0){
    char buf[1];
    read(p[0], buf, 1);
    fprintf(1, "%d: received ping\n", getpid());
    write(p[1], buf, 1);
    close(p[0]);
    close(p[1]);
    exit(0);
  } else {
    printf("fork error\n");
  }

  exit(0);
}