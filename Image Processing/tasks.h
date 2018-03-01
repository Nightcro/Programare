#define FlSize 3

//Program realizat de Mindru Alexandru-Ionut
//Grupa 311CB

void tasks(image temp, char *filename, unsigned int threshold, char *compress);
BitMap **task_1(image temp);
BitMap **task_2(image temp, signed char filter[FlSize][FlSize]);
void task_3(image temp, int threshold);
void task_4(char *compress);