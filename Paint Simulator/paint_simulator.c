#include <stdio.h>
#include "Pixel.h"
#include "Operations.h"
#include "Errors.h"
#define True 1

//Program realizat de Mindru Alexandru-Ionut
//Grupa 311CB

int main(void)
{
	int op, height, width, param[7];
	pixel **imagine = NULL;
	while(True)
	{
		unsigned int pass = 0;
		scanf("%d", &op); // op = numarul operatiei
		if((op != 1) && (imagine == NULL))
		{
			error_initialise_argum();
		}
		pass = get_param(param);
		if(pass == 8)
		{
			if(imagine != NULL)
			{
				free_matrix(imagine, height);
			}
			error_initialise_argum();
		}
		if(op == 1)
		{
			if(pass != 2)
			{
				if(imagine != NULL)
				{
					free_matrix(imagine, height);
				}
				error_initialise_argum();
			}
			if(imagine != NULL)
			{
				free_matrix(imagine, height);
			}
			width = param[0];
			height = param[1];
			imagine = initialise_matrix(height, width);
			read_matrix(imagine, height, width);
		}
		else if(op == 2)
		{
			if(pass != 4)
			{
				error_initialise_argum_free(imagine, height);
			}
			imagine = crop(imagine, height, width, param[0], param[1],
						param[2], param[3]);
			width = param[2] - param[0] + 1;  // se schimba dimensiunile
			height = param[3] - param[1] + 1; // imaginii dupa crop
		}
		else if(op == 3)
		{
			if(pass != 2)
			{
				error_initialise_argum_free(imagine, height);
			}
			if((param[1] <= height) && (param[0] <= width))
			{
				imagine = crop(imagine, height, width, 0, 0,
							 param[0] - 1, param[1] - 1);
			}
			else
			{
				imagine = resize(imagine, height, width, param[1], param[0]);
			}
			width = param[0];
			height = param[1];
		}
		else if(op == 4)
		{
			if(pass != 7)
			{
				error_initialise_argum_free(imagine, height);
			}
			color_region(imagine, height, width, param[0], param[1],
					 param[2], param[3], param[4], param[5], param[6]);
		}
		else if(op == 5)
		{
			if(pass != 1)
			{
				error_initialise_argum_free(imagine, height);
			}
			imagine = blur(imagine, height, width, param[0]);
		}
		else if(op == 6)
		{
			if(pass != 1)
			{
				error_initialise_argum_free(imagine, height);
			}
			imagine = rotation(imagine, height, width, param[0]);
			if(param[0] % 2 != 0)
			{
				height = height + width; // se face matematic 
				width = height - width;  // interchimbarea celor 2 valori
				height = height - width;
			}
		}
		else if(op == 7)
		{
			if(pass != 5)
			{
				error_initialise_argum_free(imagine, height);
			}
			fill(imagine, height, width, param[0], param[1], 
				param[2], param[3], param[4]);
		}
		else if(op == 8)
		{
			if(pass != 0)
			{
				error_initialise_argum_free(imagine, height);
			}
			print_matrix(imagine, height, width);
		}
		else if(op == 0)
		{
			if(pass != 0)
			{
				error_initialise_argum_free(imagine, height);
			}
			free_matrix(imagine, height);
			return 0;
		}
		else
		{
			error_initialise_argum_free(imagine, height);
		}
	}
}