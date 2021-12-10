/*
  Executing command in C
  Redirectiong standard output in C
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  int pid = fork();
  if (pid == -1) {
    return 1;
  }
  if (pid == 0) {
    // child process
    int file = open("pingResult.txt", O_WRONLY | O_CREAT, 0777);
    if (file == -1) {
      return 2;
    }
    printf("The fd to pingResult: %d\n", file);
    dup2(file, STDOUT_FILENO);
    close(file);

    int err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
    if (err == -1) {
      return 3;
    }
  } else {
    wait(NULL);
    printf("Sucees!\n");
  }
  return 0;
}
