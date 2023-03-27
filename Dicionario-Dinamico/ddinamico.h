typedef struct ddinamico TDDinamico;
TDDinamico* criar_DD(int tamanho);
void inserir_DD(TDDinamico *dd, int chave, void* info);
void* buscar_DD(TDDinamico *dd, int chave);
void* remover_DD(TDDinamico *dd, int chave);
