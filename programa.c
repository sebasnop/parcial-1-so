#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    // Creacion proceso hijo
    int rc = fork();

    if (rc < 0){
        // Falla creacion proceso hijo
        printf("Fallo fork()\n");
        return(1);
    } else if (rc == 0){
        // Proceso hijo
        read(fd[0],buffer,sizeof(buffer)); //leo el pipe
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