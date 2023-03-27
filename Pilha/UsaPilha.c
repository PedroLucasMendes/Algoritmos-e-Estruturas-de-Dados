#include "stdio.h"
#include "pilha.h"
#include "stdlib.h"
#include "string.h"
#include "livro.h"


int main(int argc, char const *argv[]){
    TPilha *paraLer = criarPilha(0);
    
    char titulo[60];
    int anoPubl;

    scanf("%[^\n]%*c", titulo);
    while(strcmp(titulo,"FIM") != 0){
        scanf("%d\n",&anoPubl);

        TLivro *exemplar = criarLivro(titulo, anoPubl);
        empilhar(paraLer, exemplar);
        scanf("%[^\n]%*c", titulo);
    }
    TLivro *topo = oTopoPilha(paraLer);
    imprimirLivro(topo);

    topo = oTopoPilha(paraLer);
    imprimirLivro(topo);

    topo = desempilhar(paraLer);
    free(topo);

    printf("altura: %d\n", alturaPilha(paraLer));

    topo = oTopoPilha(paraLer);
    imprimirLivro(topo);

    return 0;
}
