#include "stdio.h"
#include "abb.h"
#include "stdlib.h"
#include "assert.h"

typedef struct palavra{
    int pagina;
    int ocorrencia;
}TPalavra;

TPalavra* criarPalavra(int ocorrencia, int pagina){
    TPalavra* palavra = malloc(sizeof(TPalavra));

    palavra->pagina = pagina;
    palavra->ocorrencia = ocorrencia;
    

    return palavra;
}

void imprimirPalavra(void* p){
    TPalavra *pa = p;
    printf("Pagina: %d Ocorrencia: %d\n", pa->pagina, pa->ocorrencia);
}

int compararPalavra(void* p1, void* p2){
    
    //imprimirPalavra(p1);
    //imprimirPalavra(p2);
    TPalavra *palavra1 = p1;
    TPalavra *palavra2 = p2;
    //printf("transformou \n");
    return palavra1->pagina - palavra2->pagina;
}

void destruirPalavra(void* palavra){
    free(palavra);
}


int main(int argc, const char *argv[]){
    TABB *abb = criarABB(compararPalavra, imprimirPalavra, destruirPalavra);
    int pagina, ocorre;
    scanf("%d", &pagina);
    while (pagina != -1)
    {
        scanf("%d", &ocorre);
        TPalavra *palavra = criarPalavra(ocorre, pagina);
        inserirABB(abb, palavra);
        scanf("%d",&pagina);
    }
    
    imprimirABB(abb);

    scanf("%d", &pagina);
    while(pagina != -1){
        podarABB(abb, &pagina);
        
        printf("=====>podado: %d\n", pagina);
        scanf("%d", &pagina);
        imprimirABB(abb);
    }

    scanf("%d", &pagina);
    removerABB(abb, &pagina);
    imprimirABB(abb);

    return 0;
}