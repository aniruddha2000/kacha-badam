#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  int arr[] = {1, 2, 3, 4, 5, 6};
  int arrSize = sizeof(arr) / sizeof(int);
  int start, end;
  char processName[10];
  int fd[2];
  if (pipe(fd) == -1) {
    printf("NA error occured");
    return 1;
  }
  int id = fork();
  if (id == -1) {
    printf("Error with fork!");
    return 2;
  }
  if (id == 0) {
    start = 0;
    end = arrSize / 2;
    strcpy(processName, "child");
  } else {
    start = arrSize / 2;
    end = arrSize;
    strcpy(processName, "parent");
  }

  int sum = 0;
  for (int i = start; i < end; i++) {
    sum += arr[i];
  }

  printf("Calculated partial sum : %d from %s\n", sum, processName);

  if (id == 0) {
    close(fd[0]);
    write(fd[1], &sum, sizeof(sum));
    close(fd[1]);
  } else {
    int sumFromChild;
    close(fd[1]);
    read(fd[0], &sumFromChild, sizeof(sumFromChild));
    close(fd[0]);
    int totalSum = sum + sumFromChild;
    printf("Total sum : %d", totalSum);
    wait(NULL);
  }

  return 0;
}
