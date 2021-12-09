#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  int fd[2];
  if (pipe(fd) == -1) {
    printf("NA error occured");
    return 1;
  }
  int id = fork();
  if (id == -1) {
    printf("Error with fork!");
    return 4;
  }
  if (id == 0) {
    close(fd[0]);
    int x;
    printf("Enter input : ");
    scanf("%d", &x);
    if (write(fd[1], &x, sizeof(int)) == -1) {
      printf("Write didn't happened!");
      return 2;
    }
    close(fd[1]);
  } else {
    close(fd[1]);
    int y;
    if (read(fd[0], &y, sizeof(int)) == -1) {
      printf("Read didn't happened");
      return 3;
    }
    close(fd[0]);
    printf("Got from child process : %d", y);
  }

  return 0;
}
