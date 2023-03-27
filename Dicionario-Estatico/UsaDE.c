#include "stdio.h"
#include "DEstatico.h"
#include "stdlib.h"
#include "string.h"

//-fms-extensions

typedef struct pessoa
{
    int idade;
    char nome[100];
    char apelido[20];
}TPessoa;



TPessoa* criar_pessoa(int idade, char nome[], char apelido[]){
    TPessoa *p = malloc(sizeof(TPessoa));
    p->idade = idade;
    strcpy(p->nome, nome);
    strcpy(p->apelido, apelido);

    return p;
}

void Imprimir_Pessoa(TPessoa *p){
    printf("idade: %d\n nome: %s\n apelido: %s\n", p->idade, p->nome, p->apelido);
}


int main(){

    TDEstatico *pessoas = criar_DE(120);
    
    //TPessoa *fulano = criar_pessoa(50, "maria da silva", "maria");
    //TEntradaDic entrada = criar_entrada(404176, fulano);
    //carga_DE(pessoas, entrada);

    char nome[100], apelido[20];
    TPessoa *fulano;
    TEntradaDic entrada;

    for (int i = 1; i < 120; i++)
    {
        sprintf(nome, "%s %d", "joão da silva %d", i);
        sprintf(apelido, "joao %d", i);
        fulano = criar_pessoa(55, nome, apelido);
        entrada = criar_entrada(404177+i, fulano);
        carga_DE(pessoas, entrada);
    }
    
    
    
    for (int i = 1; i < 1000; i++)
    {
        fulano = buscar_DE(pessoas, 404176+i);
        if(fulano){
            Imprimir_Pessoa(fulano);
        }
        
    }

    dashboard_DE(pessoas);
    


    return 0;
}