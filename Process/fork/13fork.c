/*
  Background and foreground processes
  type ctrl+z to send the process to backgroud
  and type fg to bring back the process to foreground

  Handling signals
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void handle_sigtstp(int sig) {
  printf("\nStop not allowed\n");
}

void handle_sigcont(int sig) {
  printf("\nInput number: ");
  fflush(stdout);
}

int main(int argc, char const *argv[]) {
  struct sigaction sa;
  // sa.sa_handler = &handle_sigtstp;
  sa.sa_handler = &handle_sigcont;
  sa.sa_flags = SA_RESTART;
  // sigaction(SIGTSTP, &sa, NULL);
  sigaction(SIGCONT, &sa, NULL);

  // signal(SIGTSTP, &handle_sigtstp);

  int x;
  printf("Input number: ");
  scanf("%d", &x);
  printf("result %d * 5 = %d\n", x, x * 5);
  return 0;
}
