/**********************
steg

***********************/
#include<stdio.h>
#include<stdlib.h>
#include"imagem.h"
#include<string.h>
int main(int argc, char* argv[])
{
	/*variável de for*/
	int i;

	/*variáveis para guardar os parâmetros*/
	int modo_codificador = 0;
	char *input_file, *output_format, *output_image;
	/*variável que verifica se os parâmetros foram inseridos mais de uma vez*/
	int param_error_verifier = 0;

	
	for( i = 1; i < argc; i++)
	{
	/*verificará quais foram os parâmetros digitados e armazenará as informações 
	**entregues por eles.
	**caso o parâmetro não exista, seja digitado mais de uma vez, ou não tenha 
	**argumentos suficientes, imprimirá mensagem de erro.*/
		if( strcmp( "-e", argv[i] ) == 0 )
		{
			if( param_error_verifier > 0 )
			{
				printf("o parâmetro \"-e\" foi usado mais de uma vez\n");
				return 0;
			}
			param_error_verifier++;
			modo_codificador = 1;
			
		}else
		{
			if( strcmp("-i", argv[i]) == 0)
			{	
				if( param_error_verifier > 1 )
				{
					printf("o parâmetro \"-i\" foi usado mais de uma vez\n");
					return 0;
				}
				param_error_verifier++;
				i++;
				input_file = argv[i];
				if(input_file == NULL || input_file[0] == '-')
				{
					printf("argumentos para \"-i\" insuficientes\n");
					return 0;
				}
			}else
			{

				if( strcmp("-f", argv[i]) == 0)
				{
					if( param_error_verifier > 2 )
					{
						printf("o parâmetro \"-f\" foi usado mais de uma vez\n");
						return 0;
					}
					param_error_verifier++;
					
					i++;
					output_format = argv[i];
					if(output_format == NULL || output_format[0] == '-')
					{
						printf("argumentos para \"-f\" insuficientes\n");
						return 0;
					}
					i++;
					output_image = argv[i];
					if(output_image == NULL || output_image[0] == '-')
					{
						printf("argumentos para \"-f\" insuficientes\n");
						return 0;
					}
				}
				else
				{
					printf("O parametro \"%s\" nao existe\n", argv[i]);
					return 0;
				}

			}
			
		}
		
	}

	/*termina programa*/
	return 0;
}
