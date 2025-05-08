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

int intercala(FILE* a, FILE* b, FILE* saida, Endereco ea, Endereco eb){
    fread(&ea,sizeof(Endereco),1,a);
	fread(&eb,sizeof(Endereco),1,b);

	// eof -> End Of File
	while(!feof(a) && !feof(b))
	{
		if(compara(&ea,&eb)<0) // ea < eb
		{
			fwrite(&ea,sizeof(Endereco),1,saida);
			fread(&ea,sizeof(Endereco),1,a);
		}
		else // ea >= eb
		{
			fwrite(&eb,sizeof(Endereco),1,saida);
			fread(&eb,sizeof(Endereco),1,b);
		}
	}

	while(!feof(a))
	{
		fwrite(&ea,sizeof(Endereco),1,saida);
		fread(&ea,sizeof(Endereco),1,a);		
	}
	
	while(!feof(b))
	{
		fwrite(&eb,sizeof(Endereco),1,saida);
		fread(&eb,sizeof(Endereco),1,b);		
	}

}

int main()
{
	FILE *f, *g, *saida;
	Endereco *e;
    char nome[15]; //nome dos arquivos
	long posicao, qtd, tam;
    int num_arqs = 8;
	f = fopen("cep80.dat","rb");
	fseek(f,0,SEEK_END);
	posicao = ftell(f);
	qtd = posicao/sizeof(Endereco);
	tam = qtd/num_arqs;
	rewind(f);
	
	for(int i = 1; i <= num_arqs;i++){
		e = (Endereco*) malloc(tam*sizeof(Endereco));
		if(fread(e,sizeof(Endereco),tam,f) == tam)
		{
			printf("Lido = OK\n");
		}
		qsort(e,tam,sizeof(Endereco),compara);
		printf("Ordenado = OK\n");
		
		sprintf(nome, "a%d.dat",i);
		saida = fopen(nome,"wb");
		fwrite(e,sizeof(Endereco),tam,saida);
		fclose(saida);
		printf("Escrito = OK\n");
		free(e);
	}
	
    int n, n_novos;
    int index_arq = 1;
    FILE *a, *b;
    Endereco ea, eb;
    n = num_arqs;
    do{ 
        n = n/2;
        n_novos = num_arqs + n; 
        for(int i = num_arqs+1;i <= n_novos;i++){
            sprintf(nome, "a%d.dat",i);
            saida = fopen(nome,"wb");
            printf("%s aberto como saida\n",nome);

            sprintf(nome, "a%d.dat",index_arq);
            a = fopen(nome,"rb");
            printf("%s aberto como entrada 1\n",nome);
            index_arq++;
            sprintf(nome, "a%d.dat",index_arq);
            b = fopen(nome,"rb");
            printf("%s aberto como entrada 2\n",nome);

            intercala(a, b, saida, ea, eb);
            index_arq++;
            fclose(saida);
            fclose(a);
            fclose(b);
        } 
        num_arqs = n_novos;
    }while(n > 1);

	fclose(f);
}