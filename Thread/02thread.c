#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int x = 2;

void *routine() {
  printf("Test from threads\n");
  sleep(3);
  x++;
  printf("Value of x %d\n", x);
  printf("Ending thread\n");
}

void *routine2() {
  printf("Test from threads\n");
  sleep(3);
  printf("Value of x %d\n", x);
  printf("Ending thread\n");
}

int main(int argc, char const *argv[]) {
  pthread_t t1, t2;
  if (pthread_create(&t1, NULL, &routine, NULL) != 0) {
    return 1;
  }
  if (pthread_create(&t2, NULL, &routine2, NULL) != 0) {
    return 2;
  }
  if (pthread_join(t1, NULL) != 0) {
    return 3;
  }
  if (pthread_join(t2, NULL) != 0) {
    return 4;
  }

  return 0;
}
