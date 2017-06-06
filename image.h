#ifndef IMAGEM_H
#define IMAGEM_H
typedef struct pixel{

		int r, g, b;

}Pixel;
/*Portable aNy Map struct. we can use it for .pbm, .pgm, .ppm*/
typedef struct pnm{

	char pnm_type[3];
	int max_pixel;
	int sizej, sizei;
	Pixel **pixel;

}Pnm;
#endif

/*soon .bmp, .jpeg, .png*/

//pnm's functions will read/write any pnm files
int pnmReader(Pnm*, char*);
int pnmWritter(Pnm*, char*);
