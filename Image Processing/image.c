#include <stdio.h>
#include <stdlib.h>
#include "image.h"

//Program realizat de Mindru Alexandru-Ionut
//Grupa 311CB

BitMap **initialise_matrix(int height, int width)
{
	int i, j;
	BitMap **temp;
	temp = malloc(height * sizeof(BitMap *));
	if(temp == NULL)
	{
		exit(EXIT_FAILURE);
	}
	for(i = 0; i < height; i++)
	{
		temp[i] = calloc(width, sizeof(BitMap));
		if(temp[i] == NULL)
		{
			for(j = 0; j < i; j++)
			{
				free(temp[j]);
			}
			free(temp);
			exit(EXIT_FAILURE);
		}
	}
	return temp;
}

void free_matrix(BitMap **temp, int height)
{
	int i;
	for(i = 0; i < height; i++)
	{
		free(temp[i]);
	}
	free(temp);
	return;
}

image read_image(char *filename)
{
	image temp;
	FILE *in = fopen(filename, "rb");
	fread(&temp.header, sizeof(bmp_fileheader), 1, in);
	fread(&temp.info, sizeof(bmp_infoheader), 1, in);
	fseek(in, temp.header.imageDataOffset, SEEK_SET);
	int i, j, pad = ((4 - (temp.info.width % 4)) % 4);
	temp.matrix = initialise_matrix(temp.info.height, temp.info.width);
	for(i = (temp.info.height - 1); i >= 0; i--)
	{
		for(j = 0; j < temp.info.width; j++)
		{
			fread(&temp.matrix[i][j], sizeof(unsigned char), 3, in);
			unsigned char swap = temp.matrix[i][j].blue;
			temp.matrix[i][j].blue = temp.matrix[i][j].red;
			temp.matrix[i][j].red = swap;
		}
		fseek(in, pad, SEEK_CUR);
	}
	fclose(in);
	return temp;
}

void write_image(FILE *out, image temp)
{
	fwrite(&temp.header, sizeof(bmp_fileheader), 1, out);
	fwrite(&temp.info, sizeof(bmp_infoheader), 1, out);
	fseek(out, temp.header.imageDataOffset, SEEK_SET);
	int i, j, pad = ((4 - (temp.info.width % 4)) % 4);
	unsigned char zero = 0;
	for(i = (temp.info.height - 1); i >= 0; i--)
	{
		for(j = 0; j < temp.info.width; j++)
		{
			unsigned char swap = temp.matrix[i][j].blue;
			temp.matrix[i][j].blue = temp.matrix[i][j].red;
			temp.matrix[i][j].red = swap;
			fwrite(&temp.matrix[i][j], sizeof(unsigned char), 3, out);
		}
		fwrite(&zero, 1, pad, out);
	}
	return;
}