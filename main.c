#include<stdio.h>
#include<stdlib.h>
#include"image.h"
#include<string.h>
int main(int argc, char* argv[])
{

	Bmp image;

	int i;

	int encoder_mode = 0;
	char *input_file, *output_format, *output_image;
	int param_error_verifier = 0;

	/*arguments handling*/
	for( i = 1; i < argc; i++)
	{
		if( strcmp( "-e", argv[i] ) == 0 )
		{
			if( param_error_verifier > 0 )
			{
				printf("the \"-e\" parameter was used more than one time\n");
				return 0;
			}
			param_error_verifier++;
			encoder_mode = 1;
			
		}else
		{
			if( strcmp("-i", argv[i]) == 0)
			{	
				if( param_error_verifier > 1 )
				{
					printf("the \"-i\" parameter was used more than one time\n");
					return 0;
				}
				param_error_verifier++;
				i++;
				input_file = argv[i];
				if(input_file == NULL || input_file[0] == '-')
				{
					printf("insuficient \"-i\" arguments\n");
					return 0;
				}
			}else
			{

				if( strcmp("-f", argv[i]) == 0)
				{
					if( param_error_verifier > 2 )
					{
						printf("the \"-f\" parameter was used more than one time\n");
						return 0;
					}
					param_error_verifier++;
					
					i++;
					output_format = argv[i];
					if(output_format == NULL || output_format[0] == '-')
					{
						printf("insuficient \"-f\" arguments\n");
						return 0;
					}
					i++;
					output_image = argv[i];
					if(output_image == NULL || output_image[0] == '-')
					{
						printf("insuficient \"-f\" arguments\n");
						return 0;
					}
				}
				else
				{
					printf("the \"%s\" parameter doesn't exist\n", argv[i]);
					return 0;
				}

			}
	
		}	

	}

	bmpReader(&image, input_file);
	bmpWritter(&image, output_image);
	return 0;
}
