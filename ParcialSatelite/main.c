#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* ABRIR ARCHIVO DE TEXTO
 * RECIBIR INFORMACION DE SATELITE
 * Trama: encabezado (9) + cantidad de numeros del mensaje < 99 + mensaje +  CRC (>0 & <99)
 * Controlar CRC == SUMA MENSAJE  
 */
typedef struct{
    char encabezado;
    char *cantidadNumeros;
    char *mensaje;
    char *crc;
    int sumaMensaje;
    int numeroCrc;
} mensajeDividido;

FILE* abrirArchivo(){
    FILE *texto = NULL;
    texto = fopen("archivo.txt", "w+"); 
    if(texto == NULL){
        exit(EXIT_FAILURE);
    }
    return texto;
}

mensajeDividido divisionArchivo(char *mensaje){
    mensajeDividido auxiliar;
    char *ptrAux = NULL;
    int cantidadNumeros = 0;
    int crc = 0;
    int sumaMensaje = 0;
    char *numero = NULL;
    numero = (char *) malloc(2);
    memset(numero, '\0', 2);
    int numeroEntero = 0;
    while(*mensaje != '\0'){
        auxiliar.encabezado = *mensaje;
        auxiliar.cantidadNumeros = (char *) malloc(sizeof(char) *3);
        memset(auxiliar.cantidadNumeros, '\0', 3);
        mensaje++;
        ptrAux = auxiliar.cantidadNumeros;
        *auxiliar.cantidadNumeros = *mensaje;
        auxiliar.cantidadNumeros++;
        mensaje++;
        *auxiliar.cantidadNumeros = *mensaje;
        mensaje++;
        auxiliar.cantidadNumeros = ptrAux;
        cantidadNumeros = atoi(auxiliar.cantidadNumeros);
        auxiliar.mensaje = (char *) malloc(sizeof(char) * (cantidadNumeros + 1));
        memset(auxiliar.mensaje, '\0', cantidadNumeros + 1);
        ptrAux = auxiliar.mensaje;
        for(int i = 0; i < cantidadNumeros; i++){
            *auxiliar.mensaje = *mensaje;
            *numero = *auxiliar.mensaje;
            numeroEntero = atoi(numero);
            memset(numero, '\0', 2);
            sumaMensaje = sumaMensaje + numeroEntero;
            auxiliar.mensaje++;
            mensaje++;
        }
        auxiliar.mensaje = ptrAux;
        auxiliar.crc = (char*) malloc(sizeof(char) * 3);
        memset(auxiliar.crc, '\0', 3);
        ptrAux = auxiliar.crc;
        *auxiliar.crc = *mensaje;
        auxiliar.crc++;
        mensaje++;
        *auxiliar.crc = *mensaje;
        auxiliar.crc = ptrAux;
        crc = atoi(auxiliar.crc);
        auxiliar.sumaMensaje = sumaMensaje;
        auxiliar.numeroCrc = crc;
        sumaMensaje = 0;
    }
    return auxiliar;
}

int main(int argc, char** argv) {
    FILE *resultados = NULL;
    resultados = abrirArchivo();
    char cadena[] = "910132468789250";
    mensajeDividido mensajeCarga = divisionArchivo(cadena);
    if(mensajeCarga.sumaMensaje != mensajeCarga.numeroCrc){
        fputs("error en numero de la trama", resultados);
    } else{
        fputs(mensajeCarga.mensaje, resultados);
    }
    return (EXIT_SUCCESS);
}

