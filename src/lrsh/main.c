#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h> 
#include <sys/types.h>
#include <sys/wait.h>
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
    printf("SENAL RECIBIDA %i\n", sig_num);
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
        exit(0);  
      } else if (pid > 0) {
        waitpid(pid, NULL, 0);  
      }
    }

    else if (string_equals(input[0], "sum")) {
      pid_t pid = fork();
      if (pid == 0) {
        float sum = atof(input[1]) + atof(input[2]);
        printf("%f\n", sum);
        exit(0);
      } else if (pid > 0) {
        waitpid(pid, NULL, 0);  
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
          exit(0);  
        } else {
          printf("False\n"); 
          exit(0);
        }
      }
      else if (pid > 0) {
        waitpid(pid, NULL, 0);  
      }
    }

    else if (string_equals(input[0], "lrexec")) {

      //creando mi array de argumentos
      int argc = 0;
      while (input[argc + 1] != NULL) { 
          argc++;
      }

      char** args = (char**)malloc((argc + 1) * sizeof(char*)); 
      args[0] = input[1]; // el ejecutable
      for (int i = 0; i < argc; i++) {
          args[i + 1] = input[i + 2]; 
      }

      pid_t pid = fork();
      switch(pid){
        case 0:
          execv(args[0], args);
          perror("execv error");
          exit(1);

        default:
          waitpid(pid, NULL, 0); 
      }
          
      free(args);

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

// referencia: https://www.geeksforgeeks.org/zombie-processes-prevention/ (para zombies)
// referencias: https://www.youtube.com/watch?v=Cn2XU9xgKHQ&list=PLssyEsGaMLoE-9UNrwZyl0J5KdhMSm1NV&index=3 (para senales)
// referencias: https://www.youtube.com/watch?v=NHkDL0EUKbQ&list=PLssyEsGaMLoE-9UNrwZyl0J5KdhMSm1NV&index=5 (para el lrexec)
