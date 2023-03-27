typedef struct avl TAVL;
typedef void(*TImprimirAVL)(void*);
typedef int(*TCompararAVL)(void*, void*);
typedef void(* TDestroyAVL)(void*);

TAVL* criarAVL(TCompararAVL comparar, TImprimirAVL impressora, TDestroyAVL destroy);
int alturaAVL(TAVL *AVL);
int tamanhoAVL(TAVL *AVL);
void destruirAVL(TAVL* AVL);
void inserirAVL(TAVL *AVL, void *info);
void imprimirAVL(TAVL *AVL);
void *buscarAVL(TAVL *AVL, void *buscado);
void removerAVL(TAVL *AVL, void *removivel);
void podarAVL(TAVL *AVL, void *podavel);
void *maiorAVL(TAVL *AVL);
void *menorAVL(TAVL *AVL);
