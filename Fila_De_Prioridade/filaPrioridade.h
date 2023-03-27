typedef struct filaPrioridade TFilaPrioridade;
typedef int (* TCompararFP) (void*,void*);

TFilaPrioridade* criarFP(int tamanho, TCompararFP comparar);

void enfileirarFP(TFilaPrioridade *f, void* elem);

void* desenfileirarFP(TFilaPrioridade *f);

int tamanhoFilaFP(TFilaPrioridade *f);

static trocar(void* elems[], int i, int j);