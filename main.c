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
        // Si falla la creacion del proceso hijo
        printf("Fallo fork()\n");
        return 2;

    } else if (rc == 0){
        // Proceso hijo
        char texto_recibido_hijo[200]; // Se crea variable donde se guarda el texto recibido
        int n; // Se crea variable donde se guarda el numero de caracteres recibidos

        // Lee el texto enviado por el padre
        if (read(padre_a_hijo[0], &n, sizeof(int)) < 0) {
            return 3;
        }
        if (read(padre_a_hijo[0], texto_recibido_hijo, sizeof(char) * n) < 0){
            return 4;
        }
        printf("Proceso hijo recibe: %s\n", texto_recibido_hijo);
        
        // Convertir a mayúsculas
        int indice = 0;
        for (indice; texto_recibido_hijo[indice] != '\0'; ++indice){
            texto_recibido_hijo[indice] = toupper(texto_recibido_hijo[indice]);
        }

        // Envia el texto convertido a mayúsculas al padre
        int m = strlen(texto_recibido_hijo) + 1;
            // Primero se envía la longitud del texto
        if (write(hijo_a_padre[1], &m, sizeof(int)) < 0){
            return 5;
        }
            // Luego se envía el texto
        if (write(hijo_a_padre[1], texto_recibido_hijo, sizeof(char) * m) < 0){
            return 5;
        }

    } else {
        // Proceso padre
        char texto_enviado_padre[200]; // Se crea variable donde se guarda el texto ingresado
        char texto_recibido_padre[200]; // Se crea variable donde se guarda el texto recibido

        // Ingreso de texto por el usuario
        printf("Ingrese cadena de texto: ");
        fgets(texto_enviado_padre, sizeof(texto_enviado_padre), stdin); // Se guarda el texto ingresado
        texto_enviado_padre[strlen(texto_enviado_padre) - 1] = '\0'; // Se elimina el salto de línea

        // Envia el texto ingresado por el usuario al hijo
        int m = strlen(texto_enviado_padre) + 1; // Se crea variable donde se guarda el numero de caracteres a enviar
            // Primero se envía la longitud del texto
        if (write(padre_a_hijo[1], &m, sizeof(int)) < 0){
            return 6;
        }
            // Luego se envía el texto
        if (write(padre_a_hijo[1], texto_enviado_padre, sizeof(char) * m) == -1){
            return 7;
        }

        //wait(NULL); // Espera al proceso hijo

        // Lee el texto enviado por el hijo
        int n;
        if (read(hijo_a_padre[0], &n, sizeof(int)) < 0) {
            return 8;
        }
        if (read(hijo_a_padre[0], texto_recibido_padre, sizeof(char)*n) == -1){
            return 8;
        }
        printf("Proceso padre recibe: %s\n", texto_recibido_padre);
    }
}