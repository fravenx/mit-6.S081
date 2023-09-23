#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  char *cmd = "";
  int k = 0;
  int i;
  for(i = 1;i < argc;) {
    if(!strcmp("-n",argv[i])){
      i+=2;
    }
    else break;
  }
  cmd = argv[i];
  k = argc - i;
  char *tempargv[k + 2];
  tempargv[0] = cmd;
  for(int j = 1;j <= k ;j++) {
    tempargv[j] = argv[i + j];
  }
  while(1) {
    char buf[512];
    char *p = buf;
    int n = read(0, p, 1);
    if(n == 0) break;
    p++;
    while(1) {
      int n = read(0, p, 1);
      if(*p == '\n' || n == 0) break;
      p++;
    }
    *p = 0;
    if(fork() == 0) {
      tempargv[k] = buf;
      tempargv[k + 1] = 0;
      exec(cmd, tempargv);
      exit(0);
    }else {
      wait((int *)0);
    }
  }
  exit(0);
}
