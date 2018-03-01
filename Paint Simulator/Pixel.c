#include <stdio.h>
#include <stdlib.h>
#include "Pixel.h"
#include "Errors.h"

pixel **initialise_matrix(int height, int width)
{
	check_param(height, 1, 1024);
	check_param(width, 1, 1024);
	int i, j;
	unsigned int ENOMEM = 3;
	pixel **temp;
	temp = malloc(height * sizeof(pixel *));
	if(temp == NULL)
	{
		fflush(stdout);
		fprintf(stderr, "%d\n", ENOMEM);
		exit(EXIT_FAILURE);
	}
	for(i = 0; i < height; i++)
	{
		temp[i] = calloc(width, sizeof(pixel));
		if(temp[i] == NULL)
		{
			for(j = 0; j < i; j++)
			{
				free(temp[j]);
			}
			free(temp);
			fflush(stdout);
			fprintf(stderr, "%d\n", ENOMEM);
			exit(EXIT_FAILURE);
		}
	}
	return temp;
}

void free_matrix(pixel **temp, int height)
{
	int i;
	for(i = 0; i < height; i++)
	{
		free(temp[i]);
	}
	free(temp);
	return;
}

void read_matrix(pixel **temp, int height, int width)
{
	int i, j, red, green, blue;
	for(i = 0; i < height; i++)
	{
		for(j = 0; j < width; j++)
		{	// citim numerele sub forma de int pentru a le putea verifica
			scanf("%d %d %d", &red, &green, &blue); // chiar daca in struct
			check_param_free(temp, height, red, 0, 255); // avem hhu
			check_param_free(temp, height, green, 0, 255);
			check_param_free(temp, height, blue, 0, 255);
			temp[i][j].red = red;
			temp[i][j].green = green;
			temp[i][j].blue = blue;
		}
	}
	return;
}

void print_matrix(pixel **temp, int height, int width)
{
	printf("%d %d\n", width, height);
	int i, j;
	fflush(stdout);
	for(i = 0; i < height; i++)
	{
		for(j = 0; j < width; j++)
		{
			printf("%hhu ", temp[i][j].red);
			printf("%hhu ", temp[i][j].green);
			printf("%hhu ", temp[i][j].blue);
		}
		printf("\n");
	}
	return;
}