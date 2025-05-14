#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int compara(const void *e1, const void *e2)
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}

int main(int argc, char** argv){
    int inicio, fim, meio;
    inicio = 0;
    FILE *f;
	Endereco *e;
    f = fopen("a15.dat","rb");
    fseek(f,0,SEEK_END);
    int tam = ftell(f);
	fim = tam/sizeof(Endereco) - 1;
    
    Endereco e_proc;
    strcpy(e_proc.cep,argv[1]);
    
    int achou = 0;
    while(inicio <= fim && achou == 0){
        e = (Endereco*) malloc(1*sizeof(Endereco));
        meio = (inicio + fim)/2;
        fseek(f,meio*sizeof(Endereco),SEEK_SET);
        //printf("%d - %d\n", inicio, fim);
        fread(e,sizeof(Endereco),1,f);
        
        if(compara(e, &e_proc) == 0){
            achou = 1;
        }else if(compara(e, &e_proc) > 0){
            fim = meio - 1;
        }else{
            inicio = meio + 1;
        }
        
    }

    if(achou){
        printf("%s\n",e->logradouro);
    }else{
        printf("CEP nao encontrado.");
    }
    free(e);
}