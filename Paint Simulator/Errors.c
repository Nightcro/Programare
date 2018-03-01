#include <stdio.h>
#include <stdlib.h>
#include "Pixel.h"
#include "Errors.h"

void check_param(unsigned int param, unsigned int min, unsigned int max)
{
	unsigned int EINVAL = 2;
	if((param < min) || (param > max))
	{
		fflush(stdout);
		fprintf(stderr, "%d\n", EINVAL);
		exit(EXIT_FAILURE);
	}
}

void check_param_free(pixel **temp, int height, unsigned int param, 
					unsigned int min, unsigned int max)
{
	unsigned int EINVAL = 2;
	if((param < min) || (param > max))
	{
		fflush(stdout);
		fprintf(stderr, "%d\n", EINVAL);
		free_matrix(temp, height);
		exit(EXIT_FAILURE);
	}
}

void check_more_param(pixel **temp, int height, unsigned int min, 
		unsigned int start, unsigned int end, unsigned int max)
{
	unsigned int EINVAL = 2;
	if((start < min) || (start > end) || (end < start) || (end >= max))
	{
		fflush(stdout);
		fprintf(stderr, "%d\n", EINVAL);
		free_matrix(temp, height);
		exit(EXIT_FAILURE);
	}
}

void error_initialise_argum()
{
	unsigned int EPERM = 1;
	fflush(stdout);
	fprintf(stderr, "%d\n", EPERM);
	exit(EXIT_FAILURE);
}

void error_initialise_argum_free(pixel **temp, int height)
{
	unsigned int EPERM = 1;
	free_matrix(temp, height);
	fflush(stdout);
	fprintf(stderr, "%d\n", EPERM);
	exit(EXIT_FAILURE);
}

unsigned int get_param(int *param)
{
	unsigned int pass = 0;
	char aux = getchar();
	while(aux != '\n')
	{
		if(aux != ' ')
		{
			if(((aux - '0' >= 0) && (aux - '0' <= 9)) || (aux == '-'))
			{
				ungetc(aux, stdin);
			}
			if(pass == 7)
			{
				return pass;
			}
			scanf("%d", &param[pass++]);
		}
		aux = getchar();
	}
	return pass;
}