/*
  Binary Semaphore vs Mutex
*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define THREAD_NUM 8

sem_t semFuel;
pthread_mutex_t mutexFuel;

int fuel = 50;

void* routine1(void* args) {
  while (1) {
    // sem_wait(&semFuel);
    pthread_mutex_lock(&mutexFuel);
    fuel += 50;
    printf("Current value is %d\n", fuel);
    // sem_post(&semFuel);
  }
}

void* routine2(void* args) {
  while (1) {
    // sem_post(&semFuel);
    pthread_mutex_unlock(&mutexFuel);
    usleep(5000);
  }
}

int main(int argc, char* argv[]) {
  pthread_t th[THREAD_NUM];

  pthread_mutex_init(&mutexFuel, NULL);
  sem_init(&semFuel, 0, 1);

  int i;
  for (i = 0; i < THREAD_NUM; i++) {
    if (i % 2 == 0) {
      if (pthread_create(&th[i], NULL, &routine1, NULL) != 0) {
        perror("Failed to create thread");
      }
    } else {
      if (pthread_create(&th[i], NULL, &routine2, NULL) != 0) {
        perror("Failed to create thread");
      }
    }
  }

  for (i = 0; i < THREAD_NUM; i++) {
    if (pthread_join(th[i], NULL) != 0) {
      perror("Failed to join thread");
    }
  }

  pthread_mutex_destroy(&mutexFuel);
  sem_destroy(&semFuel);

  return 0;
}
