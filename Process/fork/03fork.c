#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  int pid = fork();
  if (pid == 0) {
    sleep(1);
  }
  if (pid == 0) {
    printf("From child - \n");
    PIDget();
  } else {
    printf("From main - \n");
    PIDget();
  }
  int res = wait(NULL);
  if (res == -1) {
    printf("No process to wait for");
  } else {
    printf("%d finished", res);
  }
  return 0;
}
int PIDget() {
  printf("Parent PID - %d, Current PID - %d\n", getppid(), getpid());
  return 0;
}
