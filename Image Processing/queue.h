//Program realizat de Mindru Alexandru-Ionut
//Grupa 311CB

typedef struct list
{
    int index_i;
    int index_j;
    struct list *tail;
}list;
 
list *create_stack();
list *push(list *temp, int i, int j);
int check(list *temp, int i, int j);