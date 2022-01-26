/*
  Barriers in thread example
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define THREAD_NUM 8

int diceValues[8];
int status[8] = {0};

pthread_barrier_t barrierRollDice;
pthread_barrier_t barrierCalculated;

void *roll_dice(void *args) {
  int index = *(int *)args;

  while (1) {
    diceValues[index] = rand() % 6 + 1;
    pthread_barrier_wait(&barrierRollDice);
    pthread_barrier_wait(&barrierCalculated);

    if (status[index] == 1) {
      printf("(%d rolled %d) I won\n", index, diceValues[index]);
    } else {
      printf("(%d rolled %d) I lost\n", index, diceValues[index]);
    }
  }

  free(args);
}

int main(int argc, char const *argv[]) {
  srand(time(NULL));

  pthread_t th[THREAD_NUM];
  pthread_barrier_init(&barrierRollDice, NULL, THREAD_NUM + 1);
  pthread_barrier_init(&barrierCalculated, NULL, THREAD_NUM + 1);

  int i;
  for (i = 0; i < THREAD_NUM; i++) {
    int *a = malloc(sizeof(int));
    *a = i;
    if (pthread_create(&th[i], NULL, &roll_dice, a) != 0) {
      perror("Failed to create thread");
      return 1;
    }
  }

  while (1) {
    pthread_barrier_wait(&barrierRollDice);
    int max = 0;
    for (i = 0; i < THREAD_NUM; i++) {
      if (diceValues[i] > max) {
        max = diceValues[i];
      }
    }
    for (i = 0; i < THREAD_NUM; i++) {
      if (diceValues[i] == max) {
        status[i] = 1;
      } else {
        status[i] = 0;
      }
    }
    printf("====== New Round Started ======\n");
    sleep(1);
    pthread_barrier_wait(&barrierCalculated);
  }

  for (i = 0; i < THREAD_NUM; i++) {
    if (pthread_join(th[i], NULL) != 0) {
      return 2;
    }
  }
  pthread_barrier_destroy(&barrierRollDice);
  pthread_barrier_destroy(&barrierCalculated);

  return 0;
}
