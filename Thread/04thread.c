/*
  Create threads in a loop
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int NO_OF_THREADS = 4;

int mails = 0;
pthread_mutex_t mutex;

void *routine() {
  for (int i = 0; i < 10000000; i++) {
    pthread_mutex_lock(&mutex);
    mails++;
    pthread_mutex_unlock(&mutex);
  }
}

int main(int argc, char const *argv[]) {
  pthread_t th[NO_OF_THREADS];
  int i;
  pthread_mutex_init(&mutex, NULL);

  for (i = 0; i < NO_OF_THREADS; i++) {
    if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
      perror("Failed to create thread");
      return 1;
    }

    printf("Thread %d has started\n", i);
  }

  for (i = 0; i < NO_OF_THREADS; i++) {
    if (pthread_join(th[i], NULL) != 0) {
      return 2;
    }

    printf("Thread %d has finished\n", i);
  }

  pthread_mutex_destroy(&mutex);
  printf("Number of mails - %d\n", mails);

  return 0;
}
