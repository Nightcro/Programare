#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "tasks.h"
#include "queue.h"
#define NrBGR 3
#define Extension 4
#define FlSize 3

//Program realizat de Mindru Alexandru-Ionut
//Grupa 311CB

void tasks(image temp, char *filename, unsigned int threshold, char *compress)
{
	unsigned char initial_size = strlen(filename);

	//Task1
	filename = realloc(filename, (initial_size + 13) * sizeof(char));
	if(filename == NULL)
	{
		exit(EXIT_FAILURE);
	}
	strcpy(filename + (initial_size - Extension), "_black_white.bmp");
	FILE *out = fopen(filename, "wb");
	BitMap **black_matrix = task_1(temp); // trebuie pastrata imagina originala
	BitMap **orig_matrix = temp.matrix;   // pentru task 3 asa ca o sa creeam
	temp.matrix = black_matrix;			  // o copie a ei
	write_image(out, temp);
	fclose(out);

	///Task2 - F1
	signed char F1[FlSize][FlSize] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
	filename = realloc(filename, (initial_size + 4) * sizeof(char));
	if(filename == NULL)
	{
		exit(EXIT_FAILURE);
	}
	strcpy(filename + (initial_size - Extension), "_f1.bmp");
	out = fopen(filename, "wb");
	BitMap **aux_matrix = task_2(temp, F1); // trebuie sa creeam o copie a 
	BitMap **swap = temp.matrix;			// imaginii alb-negru pentru
	temp.matrix = aux_matrix;				// a o folosi si cu celelalte
	write_image(out, temp);					// filtre
	temp.matrix = swap;
	free_matrix(aux_matrix, temp.info.height);
	fclose(out);

	//Task2 - F2
	signed char F2[FlSize][FlSize] = {{0, 1, 0}, {1, -4, 1}, {0, 1, 0}};
	filename = realloc(filename, (initial_size + 4) * sizeof(char));
	if(filename == NULL)
	{
		exit(EXIT_FAILURE);
	}
	strcpy(filename + (initial_size - Extension), "_f2.bmp");
	out = fopen(filename, "wb");
	aux_matrix = task_2(temp, F2);
	swap = temp.matrix;
	temp.matrix = aux_matrix;
	write_image(out, temp);
	temp.matrix = swap;
	free_matrix(aux_matrix, temp.info.height);
	fclose(out);

	//Task2 - F3
	signed char F3[FlSize][FlSize] = {{1, 0, -1}, {0, 0, 0}, {-1, 0, 1}};
	filename = realloc(filename, (initial_size + 4) * sizeof(char));
	if(filename == NULL)
	{
		exit(EXIT_FAILURE);
	}
	strcpy(filename + (initial_size - Extension), "_f3.bmp");
	out = fopen(filename, "wb");
	aux_matrix = task_2(temp, F3);
	swap = temp.matrix;
	temp.matrix = aux_matrix;
	write_image(out, temp);
	temp.matrix = swap;
	free_matrix(aux_matrix, temp.info.height);
	fclose(out);
	
	free(filename);
	temp.matrix = orig_matrix;
	free_matrix(black_matrix, temp.info.height);

	//Task3
	task_3(temp, threshold);
	free_matrix(temp.matrix, temp.info.height);

	//Task4
	task_4(compress);
	free(compress);

	return;
}

BitMap **task_1(image temp)
{
	BitMap **aux_matrix = initialise_matrix(temp.info.height, temp.info.width);
	int i, j;
	for(i = 0; i < temp.info.height; i++)
	{
		for(j = 0; j < temp.info.width; j++)
		{
			unsigned int red = temp.matrix[i][j].red;
			unsigned int green = temp.matrix[i][j].green;
			unsigned int blue = temp.matrix[i][j].blue;
			aux_matrix[i][j].red = (blue + green + red) / NrBGR;
			aux_matrix[i][j].green = (blue + green + red) / NrBGR;
			aux_matrix[i][j].blue = (blue + green + red) / NrBGR;
		}
	}
	return aux_matrix;
}

BitMap **task_2(image temp, signed char filter[FlSize][FlSize])
{
	BitMap **aux_matrix = initialise_matrix(temp.info.height, temp.info.width);
	int i, j;
	for(i = 0; i < temp.info.height; i++)
	{
		for(j = 0; j < temp.info.width; j++)
		{
			int red = 0, green = 0, blue = 0;
			if(j - 1 >= 0)
			{
				red += temp.matrix[i][j - 1].red * filter[1][0]; 
				green += temp.matrix[i][j - 1].green * filter[1][0];
				blue += temp.matrix[i][j - 1].blue * filter[1][0];
			}
			if(j + 1 != temp.info.width)
			{
				red += temp.matrix[i][j + 1].red * filter[1][2];
				green += temp.matrix[i][j + 1].green * filter[1][2];
				blue += temp.matrix[i][j + 1].blue * filter[1][2];
			}
			if(i - 1 >= 0)
			{
				red += temp.matrix[i - 1][j].red * filter[0][1];
				green += temp.matrix[i - 1][j].green * filter[0][1];
				blue += temp.matrix[i - 1][j].blue * filter[0][1];
			}
			if(i + 1 != temp.info.height)
			{
				red += temp.matrix[i + 1][j].red * filter[2][1];
				green += temp.matrix[i + 1][j].green * filter[2][1];
				blue += temp.matrix[i + 1][j].blue * filter[2][1];
			}
			if((j - 1 >= 0) && (i - 1 >= 0))
			{
				red += temp.matrix[i - 1][j - 1].red * filter[0][0]; 
				green += temp.matrix[i - 1][j - 1].green * filter[0][0];
				blue += temp.matrix[i - 1][j - 1].blue * filter[0][0];
			}
			if((j - 1 >= 0) && (i + 1 != temp.info.height))
			{
				red += temp.matrix[i + 1][j - 1].red * filter[2][0]; 
				green += temp.matrix[i + 1][j - 1].green * filter[2][0];
				blue += temp.matrix[i + 1][j - 1].blue * filter[2][0];
			}
			if((j + 1 != temp.info.width) && (i - 1 >= 0))
			{
				red += temp.matrix[i - 1][j + 1].red * filter[0][2];
				green += temp.matrix[i - 1][j + 1].green * filter[0][2];
				blue += temp.matrix[i - 1][j + 1].blue * filter[0][2];
			}
			if((j + 1 != temp.info.width) && (i + 1 != temp.info.height))
			{
				red += temp.matrix[i + 1][j + 1].red * filter[2][2];
				green += temp.matrix[i + 1][j + 1].green * filter[2][2];
				blue += temp.matrix[i + 1][j + 1].blue * filter[2][2];
			}
			red += temp.matrix[i][j].red * filter[1][1];
			green += temp.matrix[i][j].green * filter[1][1];
			blue += temp.matrix[i][j].blue * filter[1][1];
			if(red > 255)
			{
				aux_matrix[i][j].red = 255;
			}
			else if(red < 0)
			{
				aux_matrix[i][j].red = 0;
			}
			else
			{
				aux_matrix[i][j].red = red;
			}
			if(green > 255)
			{
				aux_matrix[i][j].green = 255;
			}
			else if(green < 0)
			{
				aux_matrix[i][j].green = 0;
			}
			else
			{
				aux_matrix[i][j].green = green;
			}
			if(blue > 255)
			{
				aux_matrix[i][j].blue = 255;
			}
			else if(blue < 0)
			{
				aux_matrix[i][j].blue = 0;
			}
			else
			{
				aux_matrix[i][j].blue = blue;
			}
		}
	}
	return aux_matrix;
}

void max_zone(image temp, int i, int j, int threshold)
{
  	list *queue = create_stack();
    queue = push(queue, i, j);
    while(queue != NULL)
    {
        list *aux = queue;
        i = aux->index_i;
        j = aux->index_j; // reprezinta functia pop :)
        queue = queue->tail;
        free(aux);
        temp.matrix[i][j].used = 1;
        int red, green, blue;
        if((j + 1 != temp.info.width) && (temp.matrix[i][j + 1].used == 0))
        {
            red = abs(temp.matrix[i][j].red - temp.matrix[i][j + 1].red);
            green = abs(temp.matrix[i][j].green - temp.matrix[i][j + 1].green);
            blue = abs(temp.matrix[i][j].blue - temp.matrix[i][j + 1].blue);
            if((red + green + blue) <= threshold)
            {
            	temp.matrix[i][j + 1] = temp.matrix[i][j];
                temp.matrix[i][j + 1].used = 0;
                if(!check(queue, i, j + 1)) // se verifica daca ceea ce se pune
                {							// pe queue exista deja, scade 
                    queue = push(queue, i, j + 1); // timpul de executie
                }
            }
        }
        if((j - 1 >= 0) && (temp.matrix[i][j - 1].used == 0))
        {
            red = abs(temp.matrix[i][j].red - temp.matrix[i][j - 1].red);
            green = abs(temp.matrix[i][j].green - temp.matrix[i][j - 1].green);
            blue = abs(temp.matrix[i][j].blue - temp.matrix[i][j - 1].blue);
            if((red + green + blue) <= threshold)
            {
            	temp.matrix[i][j - 1] = temp.matrix[i][j];
            	temp.matrix[i][j - 1].used = 0;
                if(!check(queue, i, j - 1))
                {
                    queue = push(queue, i, j - 1);
                }
            }
        }
        if((i + 1 != temp.info.height) && (temp.matrix[i + 1][j].used == 0))
        {
            red = abs(temp.matrix[i][j].red - temp.matrix[i + 1][j].red);
            green = abs(temp.matrix[i][j].green - temp.matrix[i + 1][j].green);
            blue = abs(temp.matrix[i][j].blue - temp.matrix[i + 1][j].blue);
            if((red + green + blue) <= threshold)
            {
            	temp.matrix[i + 1][j] = temp.matrix[i][j];
                temp.matrix[i + 1][j].used = 0;
                if(!check(queue, i + 1, j))
                {
                    queue = push(queue, i + 1, j);
                }
            }
        }
        if((i - 1 >= 0) && (temp.matrix[i - 1][j].used == 0))
        {
            red = abs(temp.matrix[i][j].red - temp.matrix[i - 1][j].red);
            green = abs(temp.matrix[i][j].green - temp.matrix[i - 1][j].green);
            blue = abs(temp.matrix[i][j].blue - temp.matrix[i - 1][j].blue);
            if((red + green + blue) <= threshold)
            {
            	temp.matrix[i - 1][j] = temp.matrix[i][j];
                temp.matrix[i - 1][j].used = 0;
                if(!check(queue, i - 1, j))
                {
                    queue = push(queue, i - 1, j);
                }
            }
        }
    }
}

void task_3(image temp, int threshold)
{
  	int i, j;
  	for(i = 0; i < temp.info.height; i++)
  	{
    	for(j = 0; j < temp.info.width; j++)
    	{	 // ne folosim de used pentru a
      		if(temp.matrix[i][j].used == 0)
      		{// sari peste pixelii pe care i-am verificat 
        		max_zone(temp, i, j, threshold);
      		}// vecinii si i-am pus intr-o zona
    	}
 	}
	FILE *out = fopen("compressed.bin", "wb");
	fwrite(&temp.header, sizeof(bmp_fileheader), 1, out);
	fwrite(&temp.info, sizeof(bmp_infoheader), 1, out);
	fseek(out, temp.header.imageDataOffset, SEEK_SET);
	for(i = 0; i < temp.info.height; i++)
	{
		for(j = 0; j < temp.info.width; j++)
		{
			unsigned char pass = 0;
			if((j - 1 >= 0) && 
				(temp.matrix[i][j].red == temp.matrix[i][j - 1].red) &&
				(temp.matrix[i][j].green == temp.matrix[i][j - 1].green) &&
				(temp.matrix[i][j].blue == temp.matrix[i][j - 1].blue))
			{
				pass++;
			}	
			if((j + 1 != temp.info.width) && 
				(temp.matrix[i][j].red == temp.matrix[i][j + 1].red) &&
				(temp.matrix[i][j].green == temp.matrix[i][j + 1].green) &&
				(temp.matrix[i][j].blue == temp.matrix[i][j + 1].blue))
			{
				pass++;
			}
			if((i - 1 >= 0) && 
				(temp.matrix[i][j].red == temp.matrix[i - 1][j].red) &&
				(temp.matrix[i][j].green == temp.matrix[i - 1][j].green) &&
				(temp.matrix[i][j].blue == temp.matrix[i - 1][j].blue))
			{
				pass++;
			}
			if((i + 1 != temp.info.height) && 
				(temp.matrix[i][j].red == temp.matrix[i + 1][j].red) &&
				(temp.matrix[i][j].green == temp.matrix[i  + 1][j].green) &&
				(temp.matrix[i][j].blue == temp.matrix[i + 1][j].blue))
			{
				pass++;
			}
			if(pass != 4)
			{
				unsigned short int nr_line = i + 1, nr_column = j + 1;
				fwrite(&nr_line, sizeof(unsigned short int), 1, out); 
				fwrite(&nr_column, sizeof(unsigned short int), 1, out);
				fwrite(&temp.matrix[i][j], sizeof(unsigned char), 3, out);
			}
		}
	}
	fclose(out);
	return;
}

void task_4(char *compress)
{
	image temp;
	FILE *in = fopen(compress, "rb");
	fread(&temp.header, sizeof(bmp_fileheader), 1, in);
	fread(&temp.info, sizeof(bmp_infoheader), 1, in);
	fseek(in, temp.header.imageDataOffset, SEEK_SET);
	temp.matrix = initialise_matrix(temp.info.height, temp.info.width);
	unsigned short int nr_line, nr_column;
	do
	{
		fread(&nr_line, sizeof(unsigned short int), 1, in);
		fread(&nr_column, sizeof(unsigned short int), 1, in);
		nr_line--;
		nr_column--;
		fread(&temp.matrix[nr_line][nr_column], sizeof(unsigned char), 3, in);
		temp.matrix[nr_line][nr_column].used = 1; // refolosim used pt a marca
	}while(((nr_line + 1) != temp.info.height) || // pixelii de pe margine
			((nr_column + 1) != temp.info.width));
	fclose(in);
	int i, j;
    for(i = 1; i < (temp.info.height - 1); i++)
    {
        for(j = 1; j < temp.info.width; j++)
        {
            if(temp.matrix[i][j].used == 0) // in functie de pixelii nemarcati
            {								// umplem ce se afla in interiorul
                temp.matrix[i][j] = temp.matrix[i][j - 1];	// zonelor
            }
        }
    }
    FILE *out = fopen("decompressed.bmp", "wb");
    write_image(out, temp);
    fclose(out);
    free_matrix(temp.matrix, temp.info.height);
	return;
}