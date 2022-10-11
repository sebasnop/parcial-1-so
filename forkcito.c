#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    
    printf("Proceso padre (pid:%d)\n", (int) getpid());

    // Creacion proceso hijo
    int rc = fork();

    if (rc < 0){
        // Falla creacion proceso hijo
        printf("Fallo fork()\n");
        exit(1);
    } else if (rc == 0){
        // Proceso hijo: Nuevo proceso
        printf("Proceso hijo (pid:%d)\n", (int) getpid());
    } else {
        // Proceso padre sigue por aqui
        printf("Proceso padre de (pid:%d)\n", rc);
    }

}