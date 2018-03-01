#include <stdio.h>
#include "Pixel.h"
#include "Operations.h"
#include "Errors.h"

pixel **crop(pixel **temp, int height, int width, int start_col, 
			int start_line, int end_col, int end_line)
{
	check_more_param(temp, height, 0, start_line, end_line, height);
	check_more_param(temp, height, 0, start_col, end_col, width);
	pixel **aux = initialise_matrix(end_line - start_line + 1, 
									end_col - start_col + 1);
	int i, j, k, l;
	for(i = start_line, k = 0; i <= end_line; i++, k++)
	{
		for(j = start_col, l = 0; j <= end_col; j++, l++)
		{
			aux[k][l] = temp[i][j];
		}
	}
	free_matrix(temp, height);
	return aux;
}

pixel **resize(pixel **temp, int height, int width, int h_res, int w_res)
{
	check_param_free(temp, height, h_res, 1, 1024);
	check_param_free(temp, height, w_res, 1, 1024);
	pixel **aux = initialise_matrix(h_res, w_res);
	int i, j;
	for(i = 0; i < h_res; i++)
	{
		for(j = 0; j < w_res; j++)
		{
			// temperificam daca am depasit dimensiunile originale
			// daca da, atunci tempom face acei pixeli sa fie albi
			// caz contrat copiem ce se afla inainte pe pixelul respectitemp
			if((i >= height) || (j >= width))
			{
				aux[i][j].red = 255;
				aux[i][j].green = 255;
				aux[i][j].blue = 255;
			}
			else
			{
				aux[i][j]= temp[i][j];
			}
		}
	}
	free_matrix(temp, height);
	return aux;
}

void color_region(pixel **temp, int height, int width, int start_col, 
	int start_line, int end_col, int end_line, int red, int green, int blue)
{
	check_more_param(temp, height, 0, start_line, end_line, height);
	check_more_param(temp, height, 0, start_col, end_col, width);
	check_param_free(temp, height, red, 0, 255);
	check_param_free(temp, height, green, 0, 255);
	check_param_free(temp, height, blue, 0, 255);
	int i, j;
	for(i = start_line; i <= end_line; i++)
	{
		for(j = start_col; j <= end_col; j++)
		{
			temp[i][j].red = red;
			temp[i][j].green = green;
			temp[i][j].blue = blue;
		}
	}
	return;
}

pixel **blur(pixel **temp, int height, int width, int num_iter)
{
	check_param_free(temp, height, num_iter, 0, 2000);
	int pass;
	for(pass = 0; pass < num_iter; pass++)
	{
		pixel **aux = initialise_matrix(height, width);
		int i, j;						// in prima versiunea trimisa
		for(i = 0; i < height; i++)		// existau 9 conditii asa ca
		{							    // si codul era foarte lung
			for(j = 0; j < width; j++)  // asa ca am decis sa folosesc 4
			{							// variabile, ca sa nu depasesc limita
				unsigned int numitor = 0, red = 0, green = 0, blue = 0;
				if(j - 1 >= 0)			// de 80 de caractere pe linie
				{
					red += temp[i][j - 1].red; 
					green += temp[i][j - 1].green;
					blue += temp[i][j - 1].blue;
					numitor++;
				}	
				if(j + 1 != width)
				{
					red += temp[i][j + 1].red;
					green += temp[i][j + 1].green;
					blue += temp[i][j + 1].blue;
					numitor++;
				}
				if(i - 1 >= 0)
				{
					red += temp[i - 1][j].red;
					green += temp[i - 1][j].green;
					blue += temp[i - 1][j].blue;
					numitor++;
				}
				if(i + 1 != height)
				{
					red += temp[i + 1][j].red;
					green += temp[i + 1][j].green;
					blue += temp[i + 1][j].blue;
					numitor++;
				}
				aux[i][j].red = red / numitor;
				aux[i][j].green = green / numitor;
				aux[i][j].blue = blue / numitor;
			}
		}
		free_matrix(temp, height);
		temp = aux;
	}
	return temp;
}

pixel **rotation(pixel **temp, int height, int width, int num_rot)
{
	check_param_free(temp, height, num_rot, 1, 3);
	int pass;
	for(pass = 0; pass < num_rot; pass++)
	{
		int i, j, k, retemp_h = width, retemp_w = height;
		pixel **aux = initialise_matrix(retemp_h, retemp_w);
		for(i = height - 1, k = 0; i >= 0; i--, k++)
		{
			for(j = 0; j < width; j++)
			{
				aux[j][k] = temp[i][j];
			}
		}
		free_matrix(temp, height);
		temp = aux;
		height = height + width; // se face matematic 
		width = height - width;	 // interchimbarea celor 2 tempalori
		height = height - width;
	}
	return temp;
}

void fill_recursitempe(pixel **temp, int height, int width, int start_col,
 			int start_line, int red, int green, int blue, pixel orig)
{
	if((start_line < 0) || (start_line >= height) ||
	 (start_col < 0) || (start_col >= width))
	{
		return; // se temperifica daca nu am iesit inafara matriciei
	}
	if((temp[start_line][start_col].red != orig.red) ||
		(temp[start_line][start_col].green != orig.green) ||
		(temp[start_line][start_col].blue != orig.blue))
	{			// se temperifica daca pe ceea 
		return; // ce ne aflam acum seamana
	}			// cu pixelul original
	temp[start_line][start_col].red = red;
	temp[start_line][start_col].green = green;
	temp[start_line][start_col].blue = blue;
	fill_recursitempe(temp, height, width, start_col, start_line + 1,
	 				red, green, blue, orig);
	fill_recursitempe(temp, height, width, start_col, start_line - 1,
	 				red, green, blue, orig);
	fill_recursitempe(temp, height, width, start_col + 1, start_line,
	 			 	red, green, blue, orig);
	fill_recursitempe(temp, height, width, start_col - 1, start_line,
				 	red, green, blue, orig);
}

void fill(pixel **temp, int height, int width, int start_col, int start_line, 
		int red, int green, int blue)
{	// refelosim functia check_more_param pentru 0 <= start_line < height etc.
	check_more_param(temp, height, 0, start_line, height - 1, height);
	check_more_param(temp, height, 0, start_col, width - 1, width);
	check_param_free(temp, height, red, 0, 255);
	check_param_free(temp, height, green, 0, 255);
	check_param_free(temp, height, blue, 0, 255);
	if((temp[start_line][start_col].red == red) &&
		(temp[start_line][start_col].green == green) &&
		(temp[start_line][start_col].blue == blue))
	{
		return;
	}
	pixel orig = temp[start_line][start_col];
	fill_recursitempe(temp, height, width, start_col, start_line, 
					red, green, blue, orig);
	return;
}