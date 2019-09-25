#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int idProducto;
    int cantidad;
    char *idCliente;
} venta;

FILE * abrirArchivo(){
    FILE *archivo1 = fopen("archivo.bin", "a+b");
    if(archivo1 == NULL){
        exit(EXIT_FAILURE);
    }
    return archivo1;
}

venta leerArchivo(FILE *archivo){
    venta auxiliar;
    fread(&auxiliar, sizeof(venta), 1, archivo);
    return auxiliar;
}

void escribirArchivo(venta auxiliar, FILE *archivo){
    venta condicional;
    int flag = 0;
    fseek(archivo, sizeof(venta), SEEK_SET);
    while(!feof(archivo) && flag != 1){
        fread(&condicional, sizeof(venta), 1, archivo);
        if(condicional.idProducto == auxiliar.idProducto){
            flag = 1;
            auxiliar.cantidad += condicional.cantidad;
            fprintf(archivo, "Id del producto: %d, Id del cliente: %s, Cantidad: %d \n", auxiliar.idProducto, auxiliar.idCliente, auxiliar.cantidad);
            /// fwrite(&auxiliar, sizeof(venta), 1, archivo);
        }
    }
}


int main(int argc, char** argv) {
    FILE *archivoBin = NULL;
    FILE *archivoTxt = NULL;
    venta auxiliar;
    venta escribir;
    escribir.cantidad = 10;
    escribir.idCliente = "hoalsmwje";
    escribir.idProducto = 123;
    archivoTxt = fopen("archivo.txt", "r+");
    archivoBin = abrirArchivo();
    fwrite(&escribir, sizeof(venta), 1, archivoBin);
    while(!feof(archivoBin)){
        auxiliar = leerArchivo(archivoBin);
        escribirArchivo(auxiliar, archivoTxt);
    }
    return (EXIT_SUCCESS);
}

