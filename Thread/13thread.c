/*
  Static initializer
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define THREAD_NUM 2

pthread_mutex_t mutexFuel = PTHREAD_MUTEX_INITIALIZER;

void* routine(void* args) {
  sleep(1);
  printf("Finished execution\n");
}

int main(int argc, char* argv[]) {
  pthread_t th[THREAD_NUM];

  int i;
  for (i = 0; i < THREAD_NUM; i++) {
    if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
      perror("Failed to create thread");
    }
  }

  for (i = 0; i < THREAD_NUM; i++) {
    if (pthread_join(th[i], NULL) != 0) {
      perror("Failed to join thread");
    }
  }

  pthread_mutex_destroy(&mutexFuel);

  return 0;
}
