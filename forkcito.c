#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    // Creacion de arreglos para las tuberias
    int padre_a_hijo[2];
    int hijo_a_padre[2];

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
        close(padre_a_hijo[0]);
        close(hijo_a_padre[1]);

        char texto_recibido_hijo[200]; // Donde se guardara el texto recibido
        int n; // Donde se guardara numero de caracteres recibidos

        // Registra cantidad de caracteres del texto recibido
        if (read(padre_a_hijo[0], &n, sizeof(int)) < 0) {
            return 6; // Devuelve el numero si falla
        }

        // Guarda texto recibido
        if (read(padre_a_hijo[0], &texto_recibido_hijo, (sizeof(int) * n)) < 0) {
            return 7; // Devuelve el numero si falla
        }

        // Convertir a mayúsculas
        int indice = 0;
        for (indice; texto_recibido_hijo[indice] != '\0'; ++indice){
            texto_recibido_hijo[indice] = toupper(texto_recibido_hijo[indice]);
        }

        // Envia el texto convertido a mayúsculas al padre
        if (write(hijo_a_padre[1], &texto_recibido_hijo, (sizeof(char) * n)) == -1) {
            return 8;
        }

        // Bloquear envios en direccion correcta, ya que se finaliza el proceso
        close(padre_a_hijo[1]);
        close(hijo_a_padre[0]);

    } else {
        
        // PROCESO PADRE

        // Se cierran envios en sentido contrario
        close(padre_a_hijo[1]);
        close(hijo_a_padre[0]);

        // Para guardar el texto ingresado por usuario y recibido por hijo
        char texto_enviado_padre[200];
        char texto_recibido_padre[200];

        // Se pide al usuario que ingrese el texto
        printf("Ingrese cadena de texto: ");
        // Se guarda el texto ingresado
        fgets(texto_enviado_padre, sizeof(texto_enviado_padre), stdin);
        
        // Se elimina el salto de línea (Cuando el usuario da ENTER)
        texto_enviado_padre[strlen(texto_enviado_padre) - 1] = '\0';

        // Se obtiene la cantidad real de caracteres ingresados
        int n = strlen(texto_enviado_padre) + 1;

        // Se envia cantidad n de caracteres al hijo
        if (write(padre_a_hijo[1], &n, sizeof(int)) < 0) {
            return 4;
        }

        // Se envia el texto del usuario al hijo
        if (write(padre_a_hijo[1], &texto_enviado_padre, (sizeof(char) * n)) < 0) {
            return 5;
        }

        if (read(hijo_a_padre[0], &texto_enviado_padre, (sizeof(char) * n)) < 0) {
            return 9;
        }

        printf("Received string %s\n", texto_enviado_padre);

        // Bloquear envios en direccion correcta, ya que se finaliza el proceso
        close(padre_a_hijo[0]);
        close(hijo_a_padre[1]);
        
        wait(NULL);

    }

    return 0;

}