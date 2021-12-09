/*
  Make a FIFO file and Write into it
*/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  if (mkfifo("myfifo1", 0777) == -1) {
    if (errno != EEXIST) {
      printf("Couldn't create fifo file");
      return 1;
    }
  }
  int fd = open("myfifo1", O_RDWR);
  if (fd == -1) {
    printf("Couldn't open the fifo file");
    return 3;
  }
  int x = 100;
  if (write(fd, &x, sizeof(x)) == -1) {
    printf("Error happened writing");
    return 2;
  }
  close(fd);
  return 0;
}
