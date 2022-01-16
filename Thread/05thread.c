/*
  Get return value from thread
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void *roll_dice() {
  int value = (rand() % 6) + 1;
  int *result = malloc(sizeof(int));
  *result = value;
  printf("Thread result: %p\n", result);
  // return (void *)result;
  pthread_exit((void *)result);
}

int main(int argc, char const *argv[]) {
  int *res;

  srand(time(NULL));

  pthread_t th;

  if (pthread_create(&th, NULL, &roll_dice, NULL) != 0) {
    return 1;
  }
  if (pthread_join(th, (void **)&res) != 0) {
    return 2;
  }

  printf("Main res: %p\n", res);
  printf("Result: %d\n", *res);
  free(res);
  return 0;
}
