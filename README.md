# Tarea 0: Sistemas Operativos y Redes :construction:

* :pencil2: **integrantes:** Melanie Castillo y Tiare Marín

## Código :symbols:

### :computer: Cómo ejecutar este código

```bash
Primero se compila el codigo con el comando make y luego ingresar ./lrsh que es nuestro ejecutable
```

### :warning: Funcionalidades implementadas y no implementadas

##### Se implementaron las funciones:
* "hello", este comando crea un nuevo proceso, distinto al de la shell que imprime en la consola el string Hello
World!.

* "sum <num 1> <num 2>", este comando crea un nuevo proceso, distinto al de la shell que toma como input dos
numeros de punto flotante e imprime en la consola la suma de estos (resultando un float).

* "is_prime <num 1>", este comando crea un nuevo proceso, distinto al de la shell que toma como input un numero
entero y calcula si es primo, imprimiendo en la console True si es primo o False si no lo es.

* "lrexec (EXECUTABLE)(arg1) (arg2) ... (argn)", este comando toma la ruta executable de un ejecutable y los argumentos arg_i correspondiente a este ejecutable y lo ejecuta mediante un nuevo proceso, distinto al de la shell.

* "lrlist", este comando se encarga de entregar al usuario un listado de todos los programas que fueron ejecutados desde lrsh y se encuentran ejecutando en un determinado momento. En esta lista deben ir datos como:
• PID del proceso
• Nombre del ejecutable
• Tiempo de ejecucion del proceso en segundos
• Exit code en caso de que el hijo haya terminado, -1 en caso contrario.

* "lrexit", este comando termina la ejecucion de su programa. Anterior a esto, deben enviar un ´ SIGINT a cada
proceso hijo y esperar que todos terminen. En el caso que los programas no terminen pasados 10 segundos, se
eliminaran los procesos por medio de una senal SIGKILL. 

###### CONSIDERACIONES CON EL "lrlist"
* Consideramos que para este comando se listen todos los procesos considerando tanto como el hello, sum, is_prime y lrexec


##### IMPLEMENTAMOS TODAS LAS FUNCIONES


#### Consideraciones con Valgrind:
Al correr este comando no parece existir fugas de memoria como tal pero tal vez se pueda observar que exista bloques still reachable que no se han podido liberar, aun asi creemos que con la implementacion de los comandos implementados, esto no debiese ser un problema.


## Referencias

1) https://www.geeksforgeeks.org/zombie-processes-prevention/ (para zombies)

2) https://www.youtube.com/watch?v=Cn2XU9xgKHQ&list=PLssyEsGaMLoE-9UNrwZyl0J5KdhMSm1NV&index=3 (para senales)

3) https://www.youtube.com/watch?v=NHkDL0EUKbQ&list=PLssyEsGaMLoE-9UNrwZyl0J5KdhMSm1NV&index=5 (para el lrexec)

