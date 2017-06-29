#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<getopt.h>
#include"image.h"
#include"DEncode.h"
int main(int argc, char* argv[])
{
	int option;
	int i, j;
	int eflag=0, dflag=0, iflag=0, oflag=0, fflag=0, sflag=0;
	char *message, *output, *fformat, *fimage;
	while((option = getopt(argc, argv,"edi:o:f:s")) != -1 )
	{
		switch(option)
		{
			case 'e':
				if(eflag)
				{
					printf("parâmetro(s) inserido(s) errôneamente\n");
					return 0;
				}
				eflag=1;
				break;
			case 'd':
				if(dflag)
				{
					printf("parâmetro(s) inserido(s) errôneamente\n");
					return 0;
				}
				dflag=1;
				break;
			case 'i':
				if(dflag)
				{
					printf("parâmetro(s) inserido(s) errôneamente\n");
					return 0;
				}
				if(iflag)
				{
					printf("parâmetro(s) inserido(s) errôneamente\n");
					return 0;
				}
				iflag=1;
				message = optarg;
				break;
			case 'o':
				if(eflag)
				{
					printf("parâmetro(s) inserido(s) errôneamente\n");
					return 0;
				}
				if(oflag)
				{
					printf("parâmetro(s) inserido(s) errôneamente\n");
					return 0;
				}
				oflag=1;
				output = optarg;
				break;
			case 'f':
				if(fflag)
				{
					printf("parâmetro(s) inserido(s) errôneamente\n");
					return 0;
				}
				fflag=1;
				fformat = optarg;
				for(i=1;i<argc;i++)
				{
					if(strcmp(argv[i],"-f")==0)
					{
						if(i+2>=argc)
						{
							printf("parâmetro(s) inserido(s) errôneamente\n");
							return 0;
						}
						else
						{
							fimage = optarg+strlen(fformat)+1;
						}
					}
				}
				break;
			case 's':
				if(sflag)
				{
					printf("parâmetro(s) inserido(s) errôneamente\n");
					return 0;
				}
				sflag=1;
				break;
			default:
				break;
		}
	}
	if((eflag && iflag && fflag)||(dflag && oflag && fflag))
	{
		if(eflag)
		{
			if(strcmp(fformat,"ppm")==0)
			{
				FileData data;
				Pnm image;
				pnmReader(&image, fimage);
				fileReader(&data, message);
				pnmEncoder(&image, &data);
				pnmWritter(&image,fimage);
			}
			if(strcmp(fformat,"bmp")==0)
			{
				FileData data;
				Bmp image;
				bmpReader(&image, fimage);
				fileReader(&data, message);
				bmpEncoder(&image, &data);
				bmpWritter(&image, fimage);
			}
		}
		if(dflag)
		{
			if(strcmp(fformat,"ppm")==0)
			{
				FileData data;
				Pnm image;
				pnmReader(&image, fimage);
				pnmDecoder(&image,&data,image.sizei*image.sizej*3/8);
				fileWritter(&data, output);
				if(sflag)
				{
					filePrinter(&data);
				}
			}
			if(strcmp(fformat,"bmp")==0)
			{
				
				FileData data;
				Bmp image;
				bmpReader(&image, fimage);
				bmpDecoder(&image,&data,image.bInfo.biHeader.bihWidth*image.bInfo.biHeader.bihHeight*3/8);
				fileWritter(&data, output);
				if(sflag)
				{
					filePrinter(&data);
				}
			}
			
		}
	}else
	{
		printf("parâmetro(s) inserido(s) errôneamente\n");
		return 0;
	}
	return 0;
}
