#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[]) {
  int p[2];
  pipe(p);
  int x = 2;
  printf("main pid = %d, x = %d\n",getpid(), x);
  int pid = fork();
  while(x--) {
    if(pid == 0) {
        printf("child pid = %d, x = %d\n",getpid(), x);
    }else {
        wait((int *)0);
        printf("parent pid = %d, x = %d\n",getpid(), x);
         
    }
  }
  exit(0);
  
}