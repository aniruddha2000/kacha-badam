/*
  Calling fork multiple times (part 2) (With a practical example)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define PROCESS_NUM 3

int main(int argc, char const *argv[]) {
  int pids[PROCESS_NUM];
  int pipes[PROCESS_NUM + 1][2];

  for (int i = 0; i < PROCESS_NUM; i++) {
    if (pipe(pipes[i]) == -1) {
      printf("Error with creating pipe\n");
      return 1;
    }
  }

  for (int i = 0; i < PROCESS_NUM; i++) {
    pids[i] = fork();
    if (pids[i] == -1) {
      printf("Error with creating processes\n");
      return 2;
    }

    if (pids[i] == 0) {
      // Child process
      for (int j = 0; j < PROCESS_NUM + 1; j++) {
        if (i != j) {
          close(pipes[j][0]);
        }
        if (i + 1 != j) {
          close(pipes[j][1]);
        }
      }

      int x;
      if (read(pipes[i][0], &x, sizeof(int)) == -1) {
        printf("Error at readinga\n");
        return 3;
      }

      printf("(%d) got %d\n", i, x);

      x++;
      if (write(pipes[i + 1][1], &x, sizeof(int)) == -1) {
        printf("Error at writing\n");
        return 4;
      }

      printf("(%d) sent %d\n", i, x);

      close(pipes[i][0]);
      close(pipes[i + 1][1]);
      return 0;
    }
  }

  // Main process
  for (int j = 0; j < PROCESS_NUM + 1; j++) {
    if (j != PROCESS_NUM) {
      close(pipes[j][0]);
    }
    if (j != 0) {
      close(pipes[j][1]);
    }
  }

  int y = 5;
  printf("Main process sent %d\n", y);
  if (write(pipes[0][1], &y, sizeof(int)) == -1) {
    printf("Error at writing\n");
    return 5;
  }

  if (read(pipes[PROCESS_NUM][0], &y, sizeof(int)) == -1) {
    printf("Error at readingb\n");
    return 6;
  }

  printf("The final result is %d\n", y);
  close(pipes[0][1]);
  close(pipes[PROCESS_NUM][0]);

  for (int i = 0; i < PROCESS_NUM; i++) {
    wait(NULL);
  }

  return 0;
}
