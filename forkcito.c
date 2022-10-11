#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    // Creacion proceso hijo
    int rc = fork();

    if (rc < 0){
        
        // Falla creacion proceso hijo
        printf("Fallo fork()\n");
        exit(1);
    
    } else if (rc == 0){
        
        
    
    } else {
        
        // Proceso padre sigue por aqui
        printf("Proceso padre de (pid:%d)\n", rc);
    
    }

}