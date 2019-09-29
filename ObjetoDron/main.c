#include <stdio.h>
#include <stdlib.h>
typedef struct{
    char tipo[6];
    char tamanio[7];
    int cantidad;
} ObjetoDron;
/*
 * 
 */

void subsistema(ObjetoDron *lista[], int cantidad){
    FILE *archivo = fopen("archivo.dat","r+b");
    ObjetoDron *auxiliar = NULL;
    int flag = 0;
    for(int i = 0; i < cantidad; i++){
        fseek(archivo, sizeof(ObjetoDron), SEEK_SET);
        fread(&auxiliar, sizeof(ObjetoDron), 1, archivo);
        flag = 0;
        if(lista[i]->cantidad < 0){
            i++;
        }
        while(!feof(archivo) && flag == 0){
            if(lista[i]->tipo == auxiliar->tipo && lista[i]->tamanio == auxiliar->tamanio){
                fseek(archivo, sizeof(ObjetoDron) * -1, SEEK_CUR);
                lista[i]->cantidad += auxiliar->cantidad;
                fwrite(lista[i], sizeof(ObjetoDron), 1, archivo);
                flag = 1;
            }
        }
        if(flag == 0){
            fseek(archivo, sizeof(ObjetoDron), SEEK_END);
            fwrite(auxiliar, sizeof(ObjetoDron), 1, archivo);
        }
    }
}
int main(int argc, char** argv) {

    return (EXIT_SUCCESS);
}

