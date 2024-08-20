
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include "../input_manager/manager.h"

bool string_equals(char *string1, char *string2) {
  return !strcmp(string1, string2);
}

int main(int argc, char const *argv[])
{
  int status = 1;

  do {
    char** input = read_user_input();
    printf("%s\n", input[0]);


    if (string_equals(input[0], "lrexec hello")) {
      pid_t pid = fork();
      if (pid == 0) {
        printf("Hello World!");
      }
    }

    else if (string_equals(input[0], "lrexec sum")) {
      printf("%s", input[1]);
    }

  free_user_input(input);
  } while (status);
  
}

