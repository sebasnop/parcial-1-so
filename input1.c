#include <stdio.h>
#include <ctype.h>

int main(void) 
{
    while (1){
        char name[200];
        printf("Ingrese cadena de texto: ");
        fgets(name, sizeof(name), stdin);

        printf("Proceso hijo recibe: %s", name);

        for (int indice = 0; name[indice] != '\0'; ++indice){
            name[indice] = toupper(name[indice]);

        }

        printf("Proceso padre recibe de regreso: %s", name);
    }

    return 0;

}