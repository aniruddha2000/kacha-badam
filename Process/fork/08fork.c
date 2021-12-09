/*
  Send array value through FIFO files
  ref - 09fork.c
*/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  int arr[5];
  srand(time(NULL));
  int i;
  for (i = 0; i < 5; i++) {
    arr[i] = rand() % 10;
    printf("Writing array : %d\n", arr[i]);
  }
  int fd = open("sum", O_WRONLY);
  if (fd == -1) {
    return 1;
  }
  if (write(fd, arr, sizeof(int) * 5) == -1) {
    return 2;
  }
  close(fd);

  return 0;
}
