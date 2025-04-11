#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cep_ord.h"

int main()
{
	FILE *f, *g, *saida;
	Endereco *e;
	long posicao, qtd, tam;

	f = fopen("cep80.dat","rb");
	fseek(f,0,SEEK_END);
	posicao = ftell(f);
	qtd = posicao/sizeof(Endereco);
	tam = qtd/8;
	rewind(f);
	
	for(int i = 1; i <= 8;i++){
		e = (Endereco*) malloc(tam*sizeof(Endereco));
		if(fread(e,sizeof(Endereco),tam,f) == tam)
		{
			printf("Lido = OK\n");
		}
		qsort(e,tam,sizeof(Endereco),compara);
		printf("Ordenado = OK\n");
		char nome[15];
		sprintf(nome, "a%d.dat",i);
		saida = fopen(nome,"wb");
		fwrite(e,sizeof(Endereco),tam,saida);
		fclose(saida);
		printf("Escrito = OK\n");
		free(e);
	}
	/*int qt=8;
	int prox=1;
	Endereco ef, eg;
	char nome1[15], nome2[15], nomesaida[15];
	for(int j=0; qt<=15;j++){
		sprintf(nome1, "a%d.dat",prox);
		sprintf(nome2, "a%d.dat",prox+1);
		sprintf(nomesaida, "a%d.dat",qt+1);
		f = fopen(nome1,"rb");
		g = fopen(nome2,"rb");
		saida = fopen(nomesaida,"wb");
		qt++;
		fread(&ef,sizeof(Endereco),10,f);
		fread(&eg,sizeof(Endereco),10,g);
		prox=prox+2;
	}*/

	fclose(f);
}

