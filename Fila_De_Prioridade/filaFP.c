#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "filaPrioridade.h"

struct filaPrioridade{
    
    int ocupacao;

    //int primeiro;
    //int ultimo;

    int tamanho;
    short e_infinita;
    void* *elementos;

    TCompararFP compararFP;

};

TFilaPrioridade* criarFP(int tamanho, TCompararFP comparar){
    TFilaPrioridade *f = malloc(sizeof(TFilaPrioridade));
    
    f->tamanho = (tamanho>0?tamanho:4);
    f->e_infinita = (tamanho>0?0:1);   
    
    f->elementos = malloc(sizeof(void*)*f->tamanho);
    f->compararFP = comparar;


    
    f->ocupacao = 0;
    
    return f;
}

void enfileirarFP(TFilaPrioridade *f, void* elem){

    if((f->e_infinita) && (f->ocupacao == f->tamanho)){

        f->tamanho *=2;
        f->elementos = realloc(f->elementos, sizeof(void*)*f->tamanho);
    }

    f->elementos[f->ocupacao] = elem;
    f->ocupacao++; 

    //Validar a propriedade da ordem

    int i = f->ocupacao-1;
    int pai = floor((i-1)/2);
    
    while(i!= 0 && (f->compararFP(f->elementos[pai],f->elementos[i]) < 0)){
        trocar(f->elementos,i, pai);
        i = pai;
        pai = floor((i-1)/2);
    }
    
}

void* desenfileirarFP(TFilaPrioridade *f){
    

    if(f->ocupacao == 0){
        return NULL;
    }
    else{

        void *elem = f->elementos[0];
        f->ocupacao--;
        trocar(f->elementos, 0 , f->ocupacao);

        //Validar a propriedade da ordem


        int i;

        int maior = i;
        do
        {
            i = maior;
            int esquerda = (2*i)+1;
            int direita = (2*i)+2;
            if((esquerda < f->ocupacao) && (f->compararFP(f->elementos[i], f->elementos[esquerda]) < 0)){
                maior = (2*i)+1;
            }
            if((direita , f->ocupacao) && (f->compararFP(f->elementos[maior],f->elementos[direita]) < 0)){
                maior = (2*i)+2;
            }

            trocar(f->elementos, i, maior);
            
        } while (maior != i);
        

        return elem;
        
    }
}

int tamanhoFilaFP(TFilaPrioridade *f){
    return f->ocupacao;
}

static trocar(void* elems[], int i, int j){
    void* aux = elems[i];
    elems[i] = elems[j];
    elems[j] = aux;
}