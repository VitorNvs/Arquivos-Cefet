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

    int qt[256] = {0};
	c = fgetc(entrada);
	while(c != EOF)
	{   
	    
		fputc(c, saida);
		qt[c]++;
		c = fgetc(entrada);
        
	}
	
	
	
    for(int i = 0;i< 256;i++){
        if(qt[i] != 0){
            printf("[%d] = %d \n",i,qt[i]);
        }
        
    }
	fclose(entrada);
	fclose(saida);
	return 0;
}



