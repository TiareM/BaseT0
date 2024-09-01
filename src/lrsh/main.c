#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>
#include "../input_manager/manager.h"

// syscalls vistas en clase, como kill, exec, fork, y wait/waitpid

int indice_procesos = 0;

struct Process {
    pid_t pid;
    char name[64];
    double start_time;
    int exit_code;
};

// array procesos con maximo 16 procesos
struct Process procesos[16];

void terminate_children() {
    for (int i = 0; i < indice_procesos; i++) {
      kill(procesos[i].pid, SIGINT);  // Enviar SIGINT a cada hijo
    }

    sleep(10);

    // Esperar a que todos los hijos terminen
    for (int i = 0; i < indice_procesos; i++) {
      kill(procesos[i].pid, SIGKILL);
    }
}

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
  int status_wait;
  struct timeval start, end;
  double segundos;

  // Funcion que asigna a la señal SIGINT la fucion a ejecutar
  signal(SIGINT, sigintHandler);

  do {
    char** input = read_user_input();
    // printf("%s\n", input[0]);


    if (string_equals(input[0], "hello")) {
      
      gettimeofday(&start, NULL);

      pid_t pid = fork();
      if (pid == 0) {
        printf("Hello World!\n");
        exit(0);  
      } else if (pid > 0) {
        waitpid(pid, &status_wait, 0); 
        gettimeofday(&end, NULL); 

        procesos[indice_procesos].exit_code = -1;
        procesos[indice_procesos].pid = pid;
        strcpy(procesos[indice_procesos].name, input[0]);

        segundos = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
        procesos[indice_procesos].start_time = segundos;

        if (WIFEXITED(status_wait)) {
          procesos[indice_procesos].exit_code = WEXITSTATUS(status_wait);
        }

        indice_procesos += 1;
      }
    }

    else if (string_equals(input[0], "sum")) {

      gettimeofday(&start, NULL);

      pid_t pid = fork();
      if (pid == 0) {
        float sum = atof(input[1]) + atof(input[2]);
        printf("%f\n", sum);
        exit(0);
      } else if (pid > 0) {
        waitpid(pid, &status_wait, 0); 
        gettimeofday(&end, NULL); 

        procesos[indice_procesos].exit_code = -1;
        procesos[indice_procesos].pid = pid;
        strcpy(procesos[indice_procesos].name, input[0]);

        segundos = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
        procesos[indice_procesos].start_time = segundos;

        if (WIFEXITED(status_wait)) {
          procesos[indice_procesos].exit_code = WEXITSTATUS(status_wait);
        }

        indice_procesos += 1;  
      }
    }

    else if (string_equals(input[0], "is_prime")) {

      gettimeofday(&start, NULL);

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
        waitpid(pid, &status_wait, 0); 
        gettimeofday(&end, NULL); 

        procesos[indice_procesos].exit_code = -1;
        procesos[indice_procesos].pid = pid;
        strcpy(procesos[indice_procesos].name, input[0]);

        segundos = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
        procesos[indice_procesos].start_time = segundos;

        if (WIFEXITED(status_wait)) {
          procesos[indice_procesos].exit_code = WEXITSTATUS(status_wait);
        }

        indice_procesos += 1;  
      }
    }

    else if (string_equals(input[0], "lrexec")) {

      gettimeofday(&start, NULL);

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
          waitpid(pid, &status_wait, 0); 
          gettimeofday(&end, NULL); 

          procesos[indice_procesos].exit_code = -1;
          procesos[indice_procesos].pid = pid;
          strcpy(procesos[indice_procesos].name, input[0]);

          segundos = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
          procesos[indice_procesos].start_time = segundos;

          if (WIFEXITED(status_wait)) {
            procesos[indice_procesos].exit_code = WEXITSTATUS(status_wait);
          }

          indice_procesos += 1; 
      }
          
      free(args);

    }

    else if (string_equals(input[0], "lrlist")) {
      for (int i = 0; i < indice_procesos; i++) {
        printf("\nPID: %d\n", procesos[i].pid);
        printf("Name: %s\n", procesos[i].name);
        printf("Execution time: %f\n", procesos[i].start_time);
        printf("Exit code: %d\n", procesos[i].exit_code);
        printf("\n---------------------------\n");
      }
    }

    else if (string_equals(input[0], "lrexit")) {
      terminate_children();
      free_user_input(input);
      exit(0);
    }    

  free_user_input(input);
  } while (status);
  
}

// referencia: https://www.geeksforgeeks.org/zombie-processes-prevention/ (para zombies)
// referencias: https://www.youtube.com/watch?v=Cn2XU9xgKHQ&list=PLssyEsGaMLoE-9UNrwZyl0J5KdhMSm1NV&index=3 (para senales)
// referencias: https://www.youtube.com/watch?v=NHkDL0EUKbQ&list=PLssyEsGaMLoE-9UNrwZyl0J5KdhMSm1NV&index=5 (para el lrexec)
