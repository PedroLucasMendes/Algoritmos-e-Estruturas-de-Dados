#include "stdio.h"
#include "stdlib.h"
#include "DEstatico.h"


TEntradaDic criar_entrada(int chave, void* info){
    TEntradaDic e ;//= malloc(sizeof(TEntradaDic));
    e.chave = chave;
    e.info = info;

    return e;    
}


struct estatistica{
    int num_comp;
    int num_busc;
};

struct destatico{
    TEntradaDic *entradas;
    int tamanho;
    int ocupacao;

    struct estatistica;
};


TDEstatico* criar_DE(int tam){
    TDEstatico *dicio = malloc(sizeof(TDEstatico));
    dicio->tamanho = tam;
    dicio->entradas = malloc(sizeof(TEntradaDic)*dicio->tamanho);
    dicio->ocupacao = 0;

    return dicio;
}

int ocupacao_DE(TDEstatico* dicio){
    return dicio->ocupacao;
}

void* buscar_DE(TDEstatico* de, int chave){

    de->num_busc++;
    
    void* entrada = NULL;
    int inicio  = 0;
    int fim = de->ocupacao-1;

    short encontrou = 0;
    
    while ((!encontrou) && (inicio <= fim)){
        int meio = (inicio+fim)/2;
        if(de->entradas[meio].chave == chave){

            de->num_comp +=1 ;
            encontrou = 1;
            entrada = de->entradas[meio].info;

        }else if(de->entradas[meio].chave > chave){
            de->num_comp += 2;
            fim = meio-1;
        }else{
            de->num_comp += 3;
            inicio = meio+1;
        }
    }

    return entrada;
    
}

void carga_DE(TDEstatico* de, TEntradaDic entrada){
    de->entradas[de->ocupacao] = entrada;
    de->ocupacao++;
}

void dashboard_DE(TDEstatico *de){
    printf("Numero de buscas: %d\n", de->num_busc);
    printf("Numero de comparações: %d\n", de->num_comp);
    printf("Media comparacoes por busca: %.2lf\n", (double) de->num_comp/de->num_busc);
}