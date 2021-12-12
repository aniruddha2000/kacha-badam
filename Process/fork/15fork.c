/*
  Send an array through a pipe
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  int fd[2];
  if (pipe(fd) == -1) {
    return 2;
  }
  int pid = fork();
  if (pid == -1) {
    return 1;
  }
  if (pid == 0) {
    // child proccess
    close(fd[0]);
    int n, i;
    int arr[10];
    srand(time(NULL));
    n = rand() % 10 + 1;
    printf("Generated: ");
    for (i = 0; i < n; i++) {
      arr[i] = rand() % 11;
      printf("%d ", arr[i]);
    }
    if (write(fd[1], &n, sizeof(int)) < 0) {
      return 4;
    }
    printf("\nSent n = %d\n", n);
    if (write(fd[1], arr, sizeof(int) * n) < 0) {
      return 3;
    }
    close(fd[1]);
  } else {
    // parent proccess
    close(fd[1]);
    int i, n, sum = 0;
    int arr[10];
    if (read(fd[0], &n, sizeof(int)) < 0) {
      return 5;
    }
    printf("Received n: %d\n", n);
    if (read(fd[0], arr, sizeof(int) * n) < 0) {
      return 6;
    }
    close(fd[0]);
    for (i = 0; i < n; i++) {
      sum += arr[i];
    }
    printf("Result is : %d\n", sum);
    wait(NULL);
  }
  return 0;
}
