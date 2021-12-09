#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  int pid1, pid2;
  pid1 = fork();
  pid2 = fork();

  if (pid1 == 0) {
    if (pid2 == 0) {
      printf("It is process y\n");
    } else {
      printf("It is process x\n");
    }
  } else {
    if (pid2 == 0) {
      printf("It is process z\n");
    } else {
      printf("It is the main process\n");
    }
  }
  while (wait(NULL) != -1 || errno != ECHILD) {
    printf("waited for the child to finish\n");
  }

  return 0;
}
