#include <stdio.h>
#include <stdlib.h>

void kokumo(FILE *archivo){
    char *cadena = "Kokumo es una criatura magica";
    fwrite(cadena, sizeof(char), 30, archivo);
}
char* leerKokumo(FILE *archivo){
    char *ptr = (char *) malloc (sizeof(char) * 30);
    fseek(archivo, 0, SEEK_SET);
    fread(ptr, sizeof(char), 30, archivo);
    return ptr;
}

int main(int argc, char** argv) {
    FILE *archivo = NULL;
    if((archivo = fopen("archivoNuevo.txt", "r+")) == NULL){
        exit(EXIT_FAILURE);
    }
    kokumo(archivo);
    char *reader = leerKokumo(archivo);
    printf("%s", reader);
    
    return (EXIT_SUCCESS);
}
