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

int main(int argc, char**argv)
{
	FILE *f, *saida;
	Endereco *e;
	long posicao, qtd, metade;

	f = fopen("cep.dat","rb");
    e = (Endereco*) malloc(80*sizeof(Endereco));
    if(fread(e,sizeof(Endereco),80,f) == 80)
    {
        printf("Lido = OK\n");
    }
	saida = fopen("cep80.dat","wb");
    fwrite(e,sizeof(Endereco),80,saida);
    fclose(saida);

	/*for(int i = 1; i <= 8;i++){
		e = (Endereco*) malloc(tam*sizeof(Endereco));
		if(fread(e,sizeof(Endereco),tam,f) == tam)
		{
			printf("Lido = OK\n");
		}
		qsort(e,metade,sizeof(Endereco),compara);
		printf("Ordenado = OK\n");
		char nome[15];
		sprintf(nome, "a%d.dat",i);
		saida = fopen(nome,"wb");
		fwrite(e,sizeof(Endereco),tam*i,saida);
		fclose(saida);
		printf("Escrito = OK\n");
		free(e);
	}*/

	fclose(f);
}

