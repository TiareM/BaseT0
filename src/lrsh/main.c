#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h> 
#include <sys/types.h>
#include "../input_manager/manager.h"

// syscalls vistas en clase, como kill, exec, fork, y wait/waitpid

struct Process {
    pid_t pid;
    char name[64];
    time_t start_time;
    int exit_code;
};

// array procesos con maximo 16 procesos
struct Process procesos[16];

bool string_equals(char *string1, char *string2) {
  return !strcmp(string1, string2);
}

/* Funcion que se ejecuta al recibir la señal*/
void sigintHandler(int sig_num) 
{ 
    printf("\nPrueba\n"); 
    exit(0);
} 

int main(int argc, char const *argv[])
{
  int status = 1;
  // int procesos[16];
  // int indice_procesos = 0;

  // Funcion que asigna a la señal SIGINT la fucion a ejecutar
  signal(SIGINT, sigintHandler);

  do {
    char** input = read_user_input();
    // printf("%s\n", input[0]);


    if (string_equals(input[0], "hello")) {
      pid_t pid = fork();
      if (pid == 0) {
        printf("Hello World!\n");
      }
    }

    else if (string_equals(input[0], "sum")) {
      pid_t pid = fork();
      if (pid == 0) {
        float sum = atof(input[1]) + atof(input[2]);
        printf("%f\n", sum);
      }
    }

    else if (string_equals(input[0], "is_prime")) {

      pid_t pid = fork();
      if (pid == 0) {

        bool primo = true;
        int div;

        for (int i = 2; i <= atoi(input[1]) / 2; i++) {
          div = atoi(input[1]) % i;
          if (div == 0) {
            primo = false;
            break;
          }
        }

        if (primo) {
          printf("True\n");
        } else {
        printf("False\n"); 
        }
      }
    }

    else if (string_equals(input[0], "lrexec")) {

    }

    else if (string_equals(input[0], "lrlist")) {

    }

    else if (string_equals(input[0], "lrexit")) {
      free_user_input(input);
      exit(0);
    }    

  free_user_input(input);
  } while (status);
  
}
