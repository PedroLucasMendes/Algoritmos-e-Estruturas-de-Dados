#include "stdio.h"
#include "stdlib.h"
#include "avl.h"

typedef struct no TNo;
struct no {
  void* info;
  TNo* sae;
  TNo* sad;
  TNo* pai;

  int altura;
};

static TNo* _criarNo(void* carga){
  TNo *no = malloc(sizeof(TNo));
  no->pai = NULL;
  no->sae = NULL;
  no->sad = NULL;
  no->info = carga;

  no->altura = 0;

  return no;
}

struct avl{
  // callbacks
  TImprimirAVL impressora;
  TCompararAVL comparar;
  TDestroyAVL destroy;

  TNo* raiz;
  int tamanho;
};

static int calc_fb(TNo *no){
  return _alturaNo(no->sad) - _alturaNo(no->sae);
}

static TNo* rotacao_esquerda(TNo *A){
  TNo *B = A->sad;

  A->sad = B->sae;
  B->sae = A;

  A->altura = (1 + MAX(_alturaNo(A->sae), _alturaNo(A->sad)));
  B->altura = (1 + MAX(_alturaNo(B->sae), _alturaNo(B->sad)));

  return B;

}

static TNo*  rotacao_direita(TNo *A){
  TNo* B = A->sad;

  A->sae = B->sad;
  B->sad = A;

  A->altura = (1 + MAX(_alturaNo(A->sae), _alturaNo(A->sad)));
  B->altura = (1 + MAX(_alturaNo(B->sae), _alturaNo(B->sad)));

  return B;
}


TAVL* criarAVL(TCompararAVL comparar, TImprimirAVL impressora, TDestroyAVL destroy){
//TAVL* criarABB(TImprimirABB impressora, TCompararABB comparar, TDestroyABB destroy){
  TAVL *abb = malloc(sizeof(TAVL));
  // callbacks
  abb->impressora = impressora;
  abb->comparar = comparar;
  abb->destroy = destroy;

  // atributos
  abb->raiz = NULL;
  abb->tamanho = 0;
  return abb;
}

#define MAX(a,b) (a>b?a:b)
static int _alturaNo(TNo *no){
  if (no == NULL){
    return -1;
  }else{
    //return no->altura;
    return ( 1 + MAX(_alturaNo(no->sae),_alturaNo(no->sad)) );
  }
}

int alturaAVL(TAVL *ab){
    TNo *raiz = ab->raiz;
    int altura = _alturaNo(raiz);
    return altura;
}

static int _tamanhoNo(TNo *no){
  if (no==NULL){
    return 0;
  }
  return _tamanhoNo(no->sae) + _tamanhoNo(no->sad) + 1;
}

int tamanhoAVL(TAVL *abb){
  //return _tamanhoNo(abb->raiz);
  return abb->tamanho;
}

// static void _destruirNo(TNo *no, TDestroyAB destroy){
//     if (no==NULL){
//       return;
//     }else{
//       _destruirNo(no->sae, destroy);
//       _destruirNo(no->sad, destroy);
//       destroy(no->info); // Temos que ver neutralidade;
//       free(no);
//       return;
//     }
// }
//
// void destruirAB(TAB* ab){
//   _destruirNo(ab->raiz, ab->destroy);
//   free(ab);
//   //*ab = NULL;
// }

static TNo* _inserirNo(TNo *raiz, void *info, TCompararAVL comparar){
  if (raiz==NULL){
    return _criarNo(info);
  }else{
    if (comparar(raiz->info, info)>0){ // raiz->info > info (esquerda)
      raiz->sae =_inserirNo(raiz->sae, info, comparar);
      raiz->sae->pai = raiz;

      raiz->altura = (1+MAX(_alturaNo(raiz->sad), _alturaNo(raiz->sae)));
    }else{ // direita
      raiz->sad =_inserirNo(raiz->sad, info, comparar);
      raiz->sad->pai = raiz;

      raiz->altura = (1+MAX(_alturaNo(raiz->sad), _alturaNo(raiz->sae)));

    }
    int fb = calc_fb(raiz);
    if(fb > 1){

      if(calc_fb(raiz->sad) == 1){
        raiz = rotacao_esquerda(raiz);
      }else{

      }
    }else if(fb < -1){
      if(calc_fb(raiz->sae) == -1){
        raiz = rotacao_direita(raiz);
      }else{

      }
    }
    return raiz;
  }

}

void inserirAVL(TAVL *abb, void *info){
  abb->raiz = _inserirNo(abb->raiz, info, abb->comparar);
  abb->tamanho++;
}

static void _imprimirNo(TNo *no, TImprimirAVL impressora){
  if (no == NULL){
    return;
  }
  _imprimirNo(no->sae, impressora);
  impressora(no->info);
  printf("Altura: %d\n", no->altura);
  _imprimirNo(no->sad, impressora);

}

void imprimirAVL(TAVL *abb){
  _imprimirNo(abb->raiz, abb->impressora);
}

static TNo* _buscarNo(TNo *raiz, void *buscado, TCompararAVL comparar){
  TNo *sae, *sad;
  if (raiz == NULL){
    return NULL;
  }
  short status = comparar(raiz->info,buscado);
  if (status==0){
    return raiz;
  }else if (status > 0){
    return _buscarNo(raiz->sae, buscado, comparar);
  }else{
    return _buscarNo(raiz->sad, buscado, comparar);
  }
}

void *buscarAVL(TAVL *abb, void *buscado){
  TNo *no = _buscarNo(abb->raiz, buscado, abb->comparar);
  return (no?no->info:NULL);
}


static void* _podarNo(TNo* raiz, TDestroyAVL destroy){
    if (raiz==NULL)
      return NULL;

    raiz->sae = _podarNo(raiz->sae, destroy);
    raiz->sad = _podarNo(raiz->sad, destroy);
    destroy(raiz->info);
    free(raiz);
    return NULL;
}
//
//

void podarAVL(TAVL *abb, void *chave){

  TNo *podavel = _buscarNo(abb->raiz, chave, abb->comparar);

  //_imprimirNo(podavel,abb->impressora);

  if (podavel != NULL){
    int podas=_tamanhoNo(podavel);
    abb->tamanho -= podas;

    TNo* pai = podavel->pai;
    if (pai==NULL){ // podando a raiz?
      abb->raiz = _podarNo(podavel, abb->destroy);
    }else{
      if(pai->sae == podavel){ // podando a subarvore esquerda ?
        pai->sae = _podarNo(podavel, abb->destroy);
      }else{ // podando a subarvore direita?
        pai->sad = _podarNo(podavel, abb->destroy);
      }
      TNo* no = pai;
      while(no!=NULL){
        no->altura = (1 + MAX(_alturaNo(no->sad), _alturaNo(no->sae)));
        no = no->pai;
      }
    }
  }
}

void static _trocarInfo(TNo *n1, TNo *n2){
  void *aux = n1->info;
  n1->info = n2->info;
  n2->info = aux;
}



static TNo *_maiorNo(TNo *raiz){
  if (raiz == NULL){
    return NULL;
  }
  TNo *no = raiz;
  while(no->sad!=NULL){
    no = no->sad;
  }
  return no;
}


void *maiorAVL(TAVL *abb){
  TNo *no = _maiorNo(abb->raiz);

  return (no?no->info:NULL);

}

static TNo *_menorNo(TNo *raiz){
  if (raiz == NULL){
    return NULL;
  }
  TNo *no = raiz;
  while(no->sae!=NULL){
    no = no->sae;
  }
  return no;
}

void *menorAVL(TAVL *abb){
  TNo *no = _menorNo(abb->raiz);

  return (no?no->info:NULL);

}

static TNo* _removerNo(TNo *raiz, void *removido, TCompararAVL comparar, TDestroyAVL destroy){
  TNo *no = raiz;

  if (raiz == NULL){
    printf("Elemento não pertence\n");

  }else if (comparar(raiz->info, removido) > 0){
    raiz->sae = _removerNo(raiz->sae, removido, comparar, destroy);

    //raiz->altura = (1 + MAX(_alturaNo(raiz->sad), _alturaNo(raiz->sae)));


  }else if(comparar(raiz->info, removido) < 0){
    raiz->sad = _removerNo(raiz->sad, removido, comparar, destroy);

    //raiz->altura = (1 + MAX(_alturaNo(raiz->sad), _alturaNo(raiz->sae)));


  }else{
    if ((raiz->sae==NULL) && (raiz->sad==NULL)){ // folha
      destroy(raiz->info);
      free(raiz);
      raiz = NULL;
    }else if (raiz->sad==NULL) { // no so tem descentente SAE

      TNo *avo = raiz->pai;
      raiz->sae->pai = avo; // validar?
      no = raiz->sae;

      destroy(raiz->info);
      free(raiz);

      raiz = no;

    }else if(raiz->sae == NULL){ // no so tem descentente na SAD
      TNo *avo = raiz->pai;
      raiz->sad->pai = avo;
      no = raiz->sad;

      destroy(raiz->info);
      free(raiz);

      raiz = no;
    }else{ // caso em que a raiz tem dois descententes!!!
      TNo *maior = _maiorNo(raiz->sae);
      _trocarInfo(maior, raiz);
      raiz->sae = _removerNo(raiz->sae, removido, comparar, destroy);

      raiz->altura = (1 + MAX(_alturaNo(raiz->sad), _alturaNo(raiz->sae)));
    }
  }
  return raiz;
}

void removerAVL(TAVL *abb, void *removivel){
    TNo *raiz = abb->raiz;
    if(raiz!=NULL){
      abb->raiz = _removerNo(abb->raiz, removivel, abb->comparar, abb->destroy);
    }
}