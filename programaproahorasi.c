#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {

    // Creacion de las tuberias
    int hijo_a_padre[2];
    int padre_a_hijo[2];

    if (pipe(hijo_a_padre) < 0){
        printf("Error al crear la tuberia 1");
        return 1;
    }
    if (pipe(padre_a_hijo) < 0){
        printf("Error al crear la tuberia 2");
        return 1;
    }

    // Creacion proceso hijo
    int rc = fork();

    if (rc < 0){
        // Falla creacion proceso hijo
        printf("Fallo fork()\n");
        return 1;

    } else if (rc == 0){
        // Proceso hijo
        int x;
        if (read(padre_a_hijo[0], &x, sizeof(x)) < 0){
            return 1;
        }
        printf("Proceso hijo recibe: %s", x);
        x = x * 2;
        if (write(hijo_a_padre[1], &x, sizeof(x)) < 0){
            return 1;
        }

    } else {
        // Proceso padre
        char texto[200]; // Se crea variable donde se guarda el texto ingresado
        printf("Ingrese cadena de texto: ");
        fgets(texto, sizeof(texto), stdin);
        texto[strlen(texto) - 1] = '\0';
        if (write(padre_a_hijo[1], texto, strlen(texto) + 1) < 0){
            return 1;
        }
        wait(NULL); // Espero al proceso hijo
        if (read(hijo_a_padre[0], texto, strlen(texto) + 1) < 0){ // No se si texto u otra variable
            return 1;
        }
        printf("Proceso padre recibe: %s", texto);
    }
}