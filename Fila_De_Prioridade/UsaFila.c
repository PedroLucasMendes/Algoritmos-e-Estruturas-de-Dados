#include "stdio.h"
#include "fila.h"
#include "stdlib.h"
#include "string.h"
#include "livro.h"


int main(int argc, char const *argv[]){
    TFila *paraLer = criarFila(3);
    
    char titulo[60];
    int anoPubl;

    scanf("%[^\n]%*c", titulo);
    while(strcmp(titulo,"FIM") != 0){
        scanf("%d\n",&anoPubl);

        TLivro *exemplar = criarLivro(titulo, anoPubl);
        enfileirar(paraLer, exemplar);
        scanf("%[^\n]%*c", titulo);
    }
    TLivro *primeiro = desenfileirar(paraLer);
    imprimirLivro(primeiro);
    free(primeiro);


    printf("tamanho: %d\n", tamanhoFila(paraLer));


    return 0;
}
