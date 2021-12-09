/*
  Two way communication using the pipes
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  int p1[2];
  if (pipe(p1) == -1) {
    return 1;
  }
  int pid = fork();
  if (pid == -1) {
    return 2;
  }
  if (pid == 0) {
    int x;
    if (read(p1[0], &x, sizeof(x)) == -1) {
      return 3;
    }
    printf("Received from parent : %d\n", x);
    x *= 4;
    if (write(p1[1], &x, sizeof(x)) == -1) {
      return 4;
    }
    printf("Wrote to parent : %d\n", x);
  } else {
    srand(time(NULL));
    int y = rand() % 10;
    if (write(p1[1], &y, sizeof(y)) == -1) {
      return 5;
    }
    printf("Wrote to child : %d\n", y);
    if (read(p1[0], &y, sizeof(y)) == -1) {
      return 6;
    }
    printf("Received from child: %d\n", y);
    wait(NULL);
  }
  close(p1[0]);
  close(p1[1]);
  return 0;
}
