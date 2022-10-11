#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {c

    // Creacion de arreglos para las tuberias
    int hijo_a_padre[2];
    int padre_a_hijo[2];

    // Manejo de excepciones al crear las tuberias
    if (pipe(hijo_a_padre) < 0){
        printf("Error al crear la tuberia 1");
        return 1;
    }
    if (pipe(padre_a_hijo) < 0){
        printf("Error al crear la tuberia 2");
        return 2;
    }

    // Creacion del proceso hijo
    int rc = fork();

    if (rc < 0){
        
        // Manejos de excepciones al crear proceso hijo
        printf("Fallo al crear proceso hijo\n");
        return 3;
    
    } else if (rc == 0){
        
        // PROCESO HIJO

        // Bloquear envios contrarios, solo una direccion
        close(hijo_a_padre[0]);
        close(padre_a_hijo[1]);

        char texto_recibido_hijo[200]; // Donde se guardara el texto recibido
        int n; // Donde se guardara numero de caracteres recibidos

        // Lee el texto enviado por el padre
        if (read(padre_a_hijo[0], &n, sizeof(int)) < 0) {
            return 5; // Devuelve 5 si falla
        }



    
    } else {
        
        // PROCESO PADRE

        // Para guardar el texto ingresado por usuario y recibido por hijo
        char texto_enviado_padre[200];
        char texto_recibido_padre[200];

        // Se pide al usuario que ingrese el texto
        printf("Ingrese cadena de texto: ");
        
        // Se guarda el texto ingresado
        fgets(texto_enviado_padre, sizeof(texto_enviado_padre), stdin);
        
        // Se elimina el salto de línea (Cuando el usuario da ENTER)
        texto_enviado_padre[strlen(texto_enviado_padre) - 1] = '\0';


    }

}