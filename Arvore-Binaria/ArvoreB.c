#include "stdio.h"
#include "stdlib.h"
typedef struct no TNo;

struct no
{
    void* info;
    TNo* esq;
    TNo* dir;
    TNo* pai;
};

TNo* criarNo(TNo* pai, void* c){
    
    TNo *p = malloc(sizeof(TNo));
    p->info = c;
    p->esq = NULL;
    p->dir = NULL;
    p->pai = pai;
    return p;

}

TNo* InserirArvoreB(TNo* raiz, void* info){
    if(raiz == NULL){
        TNo *novo = criarNo(raiz, info);
        return novo;
    }
    if(sorteio(0,1) == 1){
        TNo *sae = InserirArvoreB(raiz->esq, info);
        conectaRaizSAE(raiz, sae);
    }else{
        TNo *sad = InserirArvoreB(raiz->dir, info);
        conectaRaizSAD(raiz, sad);

    }
    return raiz;
}