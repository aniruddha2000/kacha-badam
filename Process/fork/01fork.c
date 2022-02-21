#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  // int pid = fork();
  // printf("Hey it's fork e.g. 1, PID : %d\n", pid);
  fork();
  fork();
  fork();
  printf("Proccess Id: %d, parent Proccess %d\n", getpid(), getppid());
  // printf("Hello\n");
  return 0;
}
