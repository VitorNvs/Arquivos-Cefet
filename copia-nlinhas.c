#include <stdio.h>

// stdout, stdin, stderr

int main()
{
	FILE *entrada, *saida;
	int c;
    
    /*
	if(argc != 3)
	{
		fprintf(stderr,"Erro na chamada do comando.\n");
		fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM] [ARQUIVO DESTINO].\n", argv[0]);
		return 1;
	}*/

	entrada = fopen("arq.txt","rb");
	if(!entrada)
	{
		fprintf(stderr,"Arquivo não pode ser aberto para leitura\n");
		return 1;
	}

	saida = fopen("copia.txt","wb");
	if(!saida)
	{
		fclose(entrada);
		fprintf(stderr,"Arquivo não pode ser aberto para escrita\n");
		return 1;
	} 

    int qtd_linhas = 0;
	c = fgetc(entrada);
	int caracter = 0;
	while(c != EOF)
	{   
	    caracter++;
        if(c == '\n'){
            qtd_linhas++;
        }
		fputc(c, saida);
		c = fgetc(entrada);
        
	}
	
	if(caracter != 0){
	    qtd_linhas++;
	}
	
    printf("Numero de linhas do arquivo: %d", qtd_linhas);
	fclose(entrada);
	fclose(saida);
	return 0;
}


