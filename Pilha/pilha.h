typedef struct pilha TPilha;

TPilha* criarPilha(int alturaMaxima);

int empilhar(TPilha *p,void* item);

void* desempilhar(TPilha *p);

void* oTopoPilha(TPilha *p);

int alturaPilha(TPilha *p);