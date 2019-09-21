#include <stdio.h>
#include <stdlib.h>

void copiarPalabra(const char *linea, char *palabra){
    while(*linea != ' ' && *linea != '\0'){
        *palabra = *linea;
        palabra++;
        linea++;
    }
}
int main(int argc, char** argv) {
    char *linea = "hola como andas";
    char *palabra = (char *) malloc(sizeof(char) * 21);
    memset(palabra, '\0', 21);
    copiarPalabra(linea, palabra);
    printf("%s", palabra);
    return (EXIT_SUCCESS);
}

