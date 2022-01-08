/*
  How to execute another program in C (using exec)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const* argv[]) {
  char* arr[] = {"ping", "google.com", NULL};
  char* env[] = {"TEST=environment variable", NULL};
  execvpe("ping", arr, env);
  return 0;
}
