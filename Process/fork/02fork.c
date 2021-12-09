#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  int pid = fork();
  int p;
  if (pid == 0) {
    p = 1;
  } else {
    p = 6;
  }

  if (pid != 0) {
    wait(NULL);
  }

  for (int i = p; i < p + 5; i++) {
    printf("%d ", i);
    fflush(stdout);
  }
  // printf("\n");

  return 0;
}
