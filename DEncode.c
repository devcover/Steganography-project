#include"DEncode.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int fileReader(FileData* data, char* fileName)
{
    FILE* channel = fopen("teste.txt","rb");
    data->data = (char*)malloc(1);
	int c = 0;
	while(1)
	{
		if((fread(&data->data[c],1,1,channel)) == 0)
		{
            if((realloc(data->data,c)) == NULL)
            {
                printf("realloc error");
                return 0;
            }
			break;
		}
		c++;
		if((realloc(data->data,c+1)) == NULL)
		{
			printf("realloc error");
			return 0;
		}
	}
    data->size = c;
    return 1;
}
int pnmEncoder(Pnm* image, FileData* data)
{
    int i, j;
    int width, height;
 
    long int bitsNeeded = data->size*8;
    long int numPixels = image->sizei*image->sizej;
    long int bitsAvailable = numPixels*3;
    unsigned char getDataBit = 0b1;
    unsigned char getImageBit = 0b1;

    if(strcmp(image->pnm_type,"P6") == 0||strcmp(image->pnm_type,"P3") == 0)
    {
        if(bitsNeeded > bitsAvailable)
        {
            printf("Not enough pixels available for enconding.\n");
            return 0;
        }
        else
        {
  
            for(j=0;j<data->size;j++)
            {
                //putting 1 byte of data in 8 pixels(1bit for each) 
                for(i=0;i<8;i++)
                {
                    width = (i+(j*8))%(image->sizej);
                    height = (int) (i+(j*8))/(image->sizej);
                    getDataBit = 0b1;
                    getImageBit = 0b1;
                    //taking the 'i' lsb of data and the lsb of image
                    getDataBit <<= i;
                    getDataBit &= data->data[j];
                    getDataBit >>= i;

                    //compare 'i' lsb of data to lsb of image .
                    //if different, change lsb image's pixel. 
                    //else, do nothing
                    
                    if( (int) ( ((j*8) + i) / numPixels) == 0)
                    {
                        getImageBit &= image->pixel[height][width].r;
                        if(getDataBit != getImageBit)
                        {
                            
                            if(getImageBit==0)
                            {
                                image->pixel[height][width].r ^= 1;
                            }
                            else
                            {
                                image->pixel[height][width].r >>= 1;
                                image->pixel[height][width].r <<= 1;
                            }
                        }
                    }
                    if( (int) (((j*8) + i) / numPixels) == 1)
                    {
                        getImageBit &= image->pixel[height][width].g;
                        if(getDataBit != getImageBit)
                        {
                            if(getImageBit==0)
                            {
                                image->pixel[height][width].g ^= 1;
                            }
                            else
                            {
                                image->pixel[height][width].g ^= 0;
                            }
                        }
                    }
                    if( (int) (((j*8) + i) / numPixels) == 2)
                    {
                        getImageBit &= image->pixel[height][width].b;
                        if(getDataBit != getImageBit)
                        {
                            if(getImageBit==0)
                            {
                                image->pixel[height][width].b ^= 1;
                            }
                            else
                            {
                                image->pixel[height][width].b ^= 0;
                            }
                        }
                    }
                    
                }
            }
        }
    }
}