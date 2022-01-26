/*
  Conditional variable
  Signaling for condition variables (pthread_cond_signal vs pthread_cond_broadcast)
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;

int fuel = 0;

void *fuel_filling(void *arg) {
  for (int i = 0; i < 5; i++) {
    pthread_mutex_lock(&mutexFuel);
    fuel += 60;
    printf("Filling fuel... %d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);
    pthread_cond_broadcast(&condFuel);
    sleep(1);
  }
}

void *car(void *arg) {
  printf("Here to get fule\n");
  pthread_mutex_lock(&mutexFuel);
  while (fuel < 40) {
    printf("No fuel, waiting...\n");
    pthread_cond_wait(&condFuel, &mutexFuel);
  }
  fuel += 40;
  printf("Got fuel left... %d\n", fuel);
  pthread_mutex_unlock(&mutexFuel);
}

int main(int argc, char const *argv[]) {
  pthread_t th[5];

  pthread_mutex_init(&mutexFuel, NULL);
  pthread_cond_init(&condFuel, NULL);
  for (int i = 0; i < 5; i++) {
    if (i == 4) {
      if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0) {
        perror("Failed to create thread");
      }
    } else {
      if (pthread_create(&th[i], NULL, &car, NULL) != 0) {
        perror("Failed to create thread");
      }
    }
  }

  for (int i = 0; i < 5; i++) {
    if (pthread_join(th[i], NULL) != 0) {
      perror("Failed to join thread");
    }
  }
  pthread_mutex_destroy(&mutexFuel);
  pthread_cond_destroy(&condFuel);

  return 0;
}
