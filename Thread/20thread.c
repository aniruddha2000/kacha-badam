/*
  Thread Pool
*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define THREAD_NUM 4

typedef struct Task {
  int a, b;
} Task;

Task taskQueqe[256];
int taskCount = 0;

pthread_mutex_t mutexQueue;
pthread_cond_t condQueue;

void executeTask(Task *task) {
  int result = task->a + task->b;
  printf("The sum of %d and %d is %d\n", task->a, task->b, result);
}

void submitTask(Task task) {
  pthread_mutex_lock(&mutexQueue);
  taskQueqe[taskCount] = task;
  taskCount++;
  pthread_mutex_unlock(&mutexQueue);
}

void *startThread(void *args) {
  while (1) {
    Task task;
    int found = 0;

    pthread_mutex_lock(&mutexQueue);

    while (taskCount == 0) {
      pthread_cond_wait(&condQueue, &mutexQueue);
    }

    found = 1;
    task = taskQueqe[0];

    int i;
    for (i = 0; i < taskCount - 1; i++) {
      taskQueqe[i] = taskQueqe[i + 1];
    }

    taskCount--;

    pthread_mutex_unlock(&mutexQueue);

    executeTask(&task);
  }
}

int main(int argc, char const *argv[]) {
  Task t1 = {
      .a = 5,
      .b = 10};

  // executeTask(&t1);

  pthread_t th[THREAD_NUM];

  pthread_mutex_init(&mutexQueue, NULL);
  pthread_cond_init(&condQueue, NULL);

  int i;
  for (i = 0; i < THREAD_NUM; i++) {
    int *a = malloc(sizeof(int));
    *a = i;
    if (pthread_create(&th[i], NULL, &startThread, a) != 0) {
      perror("Failed to create thread");
    }
  }

  srand(time(NULL));
  for (i = 0; i < 10; i++) {
    Task t = {
        .a = rand() % 100,
        .b = rand() % 100};
    submitTask(t);
  }

  for (i = 0; i < THREAD_NUM; i++) {
    if (pthread_join(th[i], NULL) != 0) {
      perror("Failed to join thread");
    }
  }

  pthread_mutex_destroy(&mutexQueue);
  pthread_cond_destroy(&condQueue);

  return 0;
}
