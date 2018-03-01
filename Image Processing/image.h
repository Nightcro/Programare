#include "bmp_header.h"

//Program realizat de Mindru Alexandru-Ionut
//Grupa 311CB

#pragma pack(1)

typedef struct
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	unsigned int used;
}BitMap;

#pragma pack()

typedef struct
{
	bmp_fileheader header;
	bmp_infoheader info;
	BitMap **matrix;
}image;

BitMap **initialise_matrix(int height, int width);
void free_matrix(BitMap **temp, int height);
image read_image(char *filename);
void write_image(FILE *out, image aux);