typedef struct
{
	unsigned char red;
	unsigned char green;
	unsigned char blue; 
}pixel;

pixel **initialise_matrix(int height, int width);
void free_matrix(pixel **temp, int height);
void read_matrix(pixel **temp, int height, int width);
void print_matrix(pixel **temp, int height, int width);