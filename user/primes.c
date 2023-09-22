#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void process(int p[]) {
    int p1[2];
    pipe(p1);
    close(p[1]);
    int k = -1;
    int pid = 0;
    int newProcessCreated = 0;
    while(1) {
        int w;
        int n = read(p[0], &w, sizeof(w));
        if(n == 0) {
            close(p[0]);
            close(p1[1]);
            close(p1[0]);
            if(pid > 0) wait((int *)0);
            exit(0);
        }
        if(k == -1) {
            k = w;
            fprintf(1, "prime %d\n", k);
        }else if(w % k != 0){
            if(newProcessCreated == 0) {
                pid = fork();
                newProcessCreated = 1;
            }
            
            if(pid == 0) {
                process(p1);
            }else{
                write(p1[1], &w, sizeof(w));
                
            }
        }    
    }
}

int
main(int argc, char *argv[])
{
  int p[2];
  pipe(p);

  if(fork() == 0) {
    process(p);
  }else{
    close(p[0]);
    for(int i = 2; i <= 35; i++){
        int k = i;
        write(p[1], &k, sizeof(k));
    }
    close(p[1]);
    wait((int *) 0);
  }

  exit(0);
}

