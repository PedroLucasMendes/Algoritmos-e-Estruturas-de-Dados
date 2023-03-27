#include "stdio.h"
#include "lista.h"
#include "pilha.h"
#include "stdlib.h"

struct pilha
{
    void* *itens;
    int topo;
    int altura;
    //TListaSE *itens;
    int alturaMaxima; // se igual a zero, então é infinito
};

TPilha* criarPilha(int altura_maxima){
    TPilha *p;
    
    p = malloc(sizeof(TPilha));
    p->altura = 0;
    p->topo = -1;
    p->alturaMaxima = altura_maxima;
    //p->itens = criarLSE(NULL, NULL);

    int k_itens = (altura_maxima>0?altura_maxima:2);
    


    p->itens = malloc(sizeof(void*)*k_itens);
    return p;
}

int empilhar(TPilha *p,void* item){
    int status = 1; // verdade, ocorreu o empilhamento

    if(p && p->alturaMaxima == 0 || (p->altura < p->alturaMaxima)){
        //inserirInicioLSE(p->itens, item);
        p->topo++;
        p->itens[p->topo] = item; 
        p->altura++;
    }else{
        status = 0; // false, Não ocorreu o empilhamento
    }

    return status;
}

void* desempilhar(TPilha *p){
    void *item = NULL;

    if(p && p->altura > 0){
        //item = removerInicioLSE(p->itens);
        item = p->itens[p->topo];
        p->topo--;
        p->altura--;
    }

    return item;
}

void* oTopoPilha(TPilha *p){
    void *item = NULL;
    if(p && p->altura > 0){
        //item = acessarLSE(p->itens,1);
        item = p->itens[p->topo];
    }
    return item;
}

int alturaPilha(TPilha *p){
    if(p){
        return p->altura;
    }else{
        return -1; // Pilha indefinida
    }
    
}