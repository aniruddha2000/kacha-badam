/*
  Barriers in thread
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_barrier_t barrier;

void *routine(void *arg) {
  // while (1) {
    printf("Waiting at the barrier...\n");
    sleep(1);
    pthread_barrier_wait(&barrier);
    printf("We passed the barrier\n");
    sleep(1);
  // }
}

int main(int argc, char const *argv[]) {
  pthread_t th[3];
  int i;

  pthread_barrier_init(&barrier, NULL, 3);
  for (i = 0; i < 3; i++) {
    if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
      perror("Failed to create thread");
      return 1;
    }
  }
  for (i = 0; i < 3; i++) {
    if (pthread_join(th[i], NULL) != 0) {
      return 2;
    }
  }
  pthread_barrier_destroy(&barrier);

  return 0;
}
