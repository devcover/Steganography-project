#include"DEncode.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int fileReader(FileData* data, char* fileName)
{
    FILE* channel = fopen(fileName, "rb");
    data->data = (char*)malloc(1);
	int c = 0;
	while(1)
	{
		if((fread(&data->data[c],1,1,channel)) == 0)
		{
		    if( ( data->data = realloc(data->data,c) ) == NULL)
		    {
                printf("file might be empty\n");
		        return 0;
		    }
				break;
		}
		c++;
		if( ( data->data = realloc(data->data,c+1) ) == NULL)
		{
			printf("realloc error");
            
			return 0;
		}
	}
    data->size = c;
    return 1;
}
int fileWritter(FileData* data, char* fileName)
{
    FILE* channel = fopen(fileName,"wb");
    fwrite(data->data, 1, data->size, channel);
}
int filePrinter(FileData* data)
{
    int i;
    for(i=0;i<data->size;i++)
    {
        printf("%c",data->data[i]);
    }
    
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
    unsigned char inversor = 0b11111110;
    int runTimes;
    if(strcmp(image->pnm_type,"P6") == 0)
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
                    height = (int) ((i+(j*8))/(image->sizej))%image->sizei;
                    getDataBit = 0b1;
                    getImageBit = 0b1;
                    //taking the 'i' lsb of data and the lsb of image
                    getDataBit <<= i;
                    getDataBit &= data->data[j];
                    getDataBit >>= i;

                    //compare 'i' lsb of data to lsb of image .
                    //if different, change lsb image's pixel. 
                    //else, do nothing
                    runTimes = (int) ( ((j*8) + i) / numPixels );
                    switch(runTimes)
                    {
                        case 0:
                            getImageBit &= image->pixel[height][width].r;
                            if(getDataBit != getImageBit)
                            {
                                
                                if(getImageBit==0)
                                {
                                    image->pixel[height][width].r ^= 1;
                                }
                                else
                                {
                                    image->pixel[height][width].r &= inversor;
                                }
                            }
                            break;
                        case 1:
                            getImageBit &= image->pixel[height][width].g;
                            if(getDataBit != getImageBit)
                            {
                                if(getImageBit==0)
                                {
                                    image->pixel[height][width].g ^= 1;
                                }
                                else
                                {
                                    image->pixel[height][width].g &= inversor;
                                }
                            }
                            break;
                        case 2:
                            getImageBit &= image->pixel[height][width].b;
                            if(getDataBit != getImageBit)
                            {
                                if(getImageBit==0)
                                {
                                    image->pixel[height][width].b ^= 1;
                                }
                                else
                                {
                                    image->pixel[height][width].b &= inversor;
                                }
                            }
                            break;
                        default:
                            printf("error. no more pixels to encode\n");
                            return 0;
                    }
                }
            }
        }
    }
}
int pnmDecoder(Pnm* image, FileData* data, int size)
{
    int i, t;
    data->size = size;
    data->data = (char *) calloc(size,sizeof(char));
    unsigned char bitTransporter = 0b1;
    int height, width;
    int imageRunTimes;

    for(t=0;t<size;t++)
    {
        for(i=0;i<8;i++)
        {
            
            bitTransporter = 0b1;
            width = (i+(t*8))%(image->sizej);
            height = (int) ((i+(t*8))/(image->sizej))%image->sizei;
            imageRunTimes = (int) (i+(t*8))/ (image->sizej*image->sizei);
            if( imageRunTimes == 0 )
            {
                bitTransporter &= image->pixel[height][width].r;
                bitTransporter <<= i;
                data->data[t] += bitTransporter;
            }
                
            if( imageRunTimes == 1 )
            {
                bitTransporter &= image->pixel[height][width].g;
                bitTransporter <<= i;
                data->data[t] += bitTransporter;
            }
                
            if( imageRunTimes == 2 )
            {
                bitTransporter &= image->pixel[height][width].b;
                bitTransporter <<= i;
                data->data[t] += bitTransporter;
            }
        }
    }     
}
int bmpEncoder(Bmp* image, FileData* data)
{
    
    int i, j;
 
    long int bitsNeeded = data->size*8;
    long int numPixels = image->bInfo.biHeader.bihWidth*image->bInfo.biHeader.bihHeight;
    long int bitsAvailable = numPixels*3;

    unsigned char getDataBit = 0b1;
    unsigned char getImageBit = 0b1;
    unsigned char inversor = 0b11111110;
    if(bitsNeeded > bitsAvailable)
    {
        printf("Not enough pixels available for enconding.\n");
        return 0;
    }
    else
    {
       if(image->bInfo.biHeader.bihBitCount==24)
       {
            for(j=0;j<data->size;j++)
            {
                //putting 1 byte of data in 8 pixels(1bit for each) 
                for(i=0;i<8;i++)
                {
                    getDataBit = 0b1;
                    getImageBit = 0b1;
                    //taking the 'i' lsb of data and the lsb of image
                    getDataBit <<= i;
                    getDataBit &= data->data[j];
                    getDataBit >>= i;

                    //compare 'i' lsb of data to lsb of image .
                    //if different, change lsb image's pixel. 
                    //else, do nothing
                    //getImageBit &= image->pixel[height][width].r;
                    getImageBit &= image->pixels[(j*8)+i];
                    if(getDataBit != getImageBit)
                    {  
                        if(getImageBit==0)
                        {
                            image->pixels[(j*8)+i] ^= 1;
                        }
                         else
                        {
                            image->pixels[(j*8)+i] &= inversor;
                        }
                    }
                }
            }
       } 
        
    }
}
int bmpDecoder(Bmp* image, FileData* data, long int size)
{
    int i, j;
    data->size = size;
    data->data = (char *) calloc(size,sizeof(char));
    unsigned char bitTransporter = 0b1;
    for(j=0;j<size;j++)
    {
        for(i=0;i<8;i++)
        {
            
            bitTransporter = 0b1;
            bitTransporter &= image->pixels[(j*8)+i];
            bitTransporter <<= i;
            data->data[j] += bitTransporter;
        }
    }
}