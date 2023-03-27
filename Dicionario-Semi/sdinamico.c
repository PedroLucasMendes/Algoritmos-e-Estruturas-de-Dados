#include "dsdinamico.h"

typedef int(*TFuncaohash) (int);

typedef struct entrada{
    int chave;
    void* info;
}TEntradaDSH;

static TEntradaDSH _criar_entrada(int chave, void* info){
    return (TEntradaDSH) {.chave=chave, .info=info}; 
}

TDSD* criar_dsd(tamanho, TFuncaoHash hashing){

}


void inserir_DSD(TDSD* hash, int chave, void* info){
    int k = hash->hashing(chave);
    hash->entradas[k] = _criar_entrada(chave,info);
    //falta tratar colisao
}

void* buscar_DSD(TDSD* hash, int chave){
    int k = hash->hashing(chave);
    TEntradaDSH e = hash->entradas[k];
    void* info = NULL;
    //tem chave na posição?
    //a chave que tá na posição é buscada?
    // teve colisão?
    return info;
}

int tamanho_DSD(TDSD* hash){

}