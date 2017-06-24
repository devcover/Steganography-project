#ifndef IMAGEM_H
#define IMAGEM_H
/*Portable aNy Map struct. we can use it for .pbm, .pgm, .ppm*/
typedef struct pixel{

		int r, g, b;

}Pixel;
typedef struct pnm{

	char pnm_type[3];
	int max_pixel;
	int sizej, sizei;
	Pixel **pixel;
}Pnm;
/*end pnm*/

/*Bmp struct*/
typedef struct{
	unsigned short ignore;//this is for memory padding be in the beggining of the struct
	unsigned short bfhType;
	unsigned int bfhSize;
	unsigned short bfhReserved1, bfhReserved2;
	unsigned int bfhOffset;
}BITMAPFILEHEADER;

typedef struct{
	unsigned int bihSize;
	unsigned int bihWidth;
	unsigned int bihHeight;
	unsigned short bihPlanes;
	unsigned short bihBitCount;
	unsigned int bihCompression;
	unsigned int bihImageSize;
	unsigned int bihXPPM;
	unsigned int bihYPPM;
	unsigned int bihClrUsed;
	unsigned int bihClrImportant;
}BITMAPINFOHEADER;

typedef struct{
	unsigned char rgbtBlue;
	unsigned char rgbtGreen;
	unsigned char rgbtRed;
	unsigned char rgbtReserved;
}RGBQUAD;

typedef struct{
	BITMAPINFOHEADER biHeader;
	RGBQUAD *biColors;
}BITMAPINFO;

typedef struct{
	BITMAPFILEHEADER bFile;
	BITMAPINFO bInfo;
	void *pixels;
}Bmp;
/*end bmp*/

#endif
typedef struct{
    long int size;
    unsigned char *data;
}FileData;

int fileReader(FileData* ,char*);
int fileWritter(FileData* , char*);
int pnmEncoder(Pnm*, FileData*);
int pnmDecoder(Pnm*, FileData*, int);