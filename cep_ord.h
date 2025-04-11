#include <stdio.h>

#ifndef __LIB_CEPORD_H__
#define __LIB_CEPORD_H__

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

int compara(void*, void*);
void intercala(FILE, FILE, FILE);

#endif