#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {

    // Creacion de las tuberias
    int hijo_a_padre[2];
    int padre_a_hijo[2];

    // Manejo de excepciones al crear las tuberias
    if (pipe(hijo_a_padre) < 0){
        printf("Error al crear la tuberia 1");
        return 1;
    }
    if (pipe(padre_a_hijo) < 0){
        printf("Error al crear la tuberia 2");
        return 1;
    }

    // Creacion del proceso hijo
    int rc = fork();

    if (rc < 0){
        // Falla creacion proceso hijo
        printf("Fallo fork()\n");
        return 1;

    } else if (rc == 0){
        // Proceso hijo
        char texto_enviado_hijo[200]; // Se crea variable donde se guarda el texto ingresado
        char texto_recibido_hijo[200]; // Se crea variable donde se guarda el texto recibido
        // Desde aqui xd
        int x;
        if (read(padre_a_hijo[0], &x, sizeof(x)) < 0){
            return 1;
        }
        printf("Proceso hijo recibe: %s", x);
        x = x * 2;
        if (write(hijo_a_padre[1], &x, sizeof(x)) < 0){
            return 1;
        }
        // Hasta aqui xd

    } else {
        // Proceso padre
        char texto_enviado_padre[200]; // Se crea variable donde se guarda el texto ingresado
        char texto_recibido_padre[200]; // Se crea variable donde se guarda el texto recibido
        printf("Ingrese cadena de texto: ");
        fgets(texto_enviado_padre, sizeof(texto_enviado_padre), stdin); 
        texto_enviado_padre[strlen(texto_enviado_padre) - 1] = '\0';
        if (write(padre_a_hijo[1], texto_enviado_padre, strlen(texto_enviado_padre) + 1) == -1){
            return 1;
        }
        wait(NULL); // Espero al proceso hijo
        if (read(hijo_a_padre[0], texto_recibido_padre, strlen(texto_recibido_padre) + 1) == -1){
            return 1;
        }
        printf("Proceso padre recibe: %s", texto_recibido_padre);
    }
}