#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "tasks.h"

//Program realizat de Mindru Alexandru-Ionut
//Grupa 311CB

int main(void)
{
	FILE *in = fopen("input.txt", "rt");
    unsigned int count = 0, threshold;
    do
    {
        count++;
    }while(getc(in) != '\n');// aflam lungimea numelui fisierului
    char *input_image = malloc(count * sizeof(char));
    if(input_image == NULL)
    {
        exit(EXIT_FAILURE);
    }
    fseek(in, 0, SEEK_SET);
    fgets(input_image, count, in);
    fscanf(in, "%u\n", &threshold);
    char *compress = malloc(count * sizeof(char));
    if(compress == NULL)
    {
        exit(EXIT_FAILURE);
    }
    fgets(compress, count, in);
    image source = read_image(input_image);
    tasks(source, input_image, threshold, compress);
    fclose(in);
    return 0;
}