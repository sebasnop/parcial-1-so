#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {

    // Creacion de las tuberias
    int padre_a_hijo[2];
    int hijo_a_padre[2];
    pipe(padre_a_hijo);
    pipe(hijo_a_padre);

    // Creacion de variables
    // char envio_padre[200]; 
    // char recibe_padre[200]; 
    // char envio_hijo[200]; 
    // char recibe_hijo[200];

    // Creacion proceso hijo
    int rc = fork();

    if (rc < 0){
        // Falla creacion proceso hijo
        printf("Fallo fork()\n");
        return(1);
    } else if (rc == 0){
        // Proceso hijo
        dup2(fd[1], 1);
        close(fd[0]);
        dup2(fd2[0], 0);
        close(fd2[1]);
        execlp("clang-format", "clang-format", (char *)NULL);
        printf("Proceso hijo recibe: %s", name);
        for (int indice = 0; name[indice] != '\0'; ++indice){
            name[indice] = toupper(name[indice]);
    } else {
        // Proceso padre sigue por aqui
        int fd[2]; // Se crea tubería sin nombre
        char name[200]; // Se crea variable donde se guarda el texto ingresado
        printf("Ingrese cadena de texto: ");
        fgets(name, sizeof(name), stdin);
        char buffer[200];
        pipe(fd); // Se crea el PIPE
        write(fd[1], name, strlen(name));// Escribo en pipe
        wait(NULL); // Espero al proceso hijo
    }
}