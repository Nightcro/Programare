#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

//Program realizat de Mindru Alexandru-Ionut
//Grupa 311CB

list *create_stack()
{
	list *temp = NULL;
	return temp;
}

list *push(list *temp, int i, int j)
{
    if(temp == NULL)
    {
        temp = (list *)malloc(sizeof(list));
        if(temp == NULL)
		{
			exit(EXIT_FAILURE);
		}
		temp->tail = NULL;
        temp->index_i = i;
        temp->index_j = j;
    }
    else
    {
    	list *aux = (list *)malloc(sizeof(list));
    	if(aux == NULL)
		{
			exit(EXIT_FAILURE);
		}
        aux->index_i = i;
        aux->index_j = j;
        aux->tail = NULL;
        list *swap = temp;
        while(swap->tail != NULL)
        {
        	swap = swap->tail;
        }
        swap->tail = aux;
    }
    return temp;
}

int check(list *temp, int i, int j)
{
    list *aux = temp;
    while(aux != NULL)
    {
        if((aux->index_i == i) && (aux->index_j == j))
        {
            return 1;
        }
        aux = aux->tail;
    }
    return 0;
}
