typedef struct entrada TEntradaDic;
typedef struct destatico TDEstatico;

struct entrada{
    int chave;
    void* info;
};

TEntradaDic criar_entrada(int chave, void* info);

TDEstatico* criar_DE(int tam);

void* buscar_DE(TDEstatico* de, int chave);

void carga_DE(TDEstatico* de, TEntradaDic entrada);

void dashboard_DE(TDEstatico *de);