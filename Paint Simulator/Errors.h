void check_param(unsigned int param, unsigned int min, unsigned int max);
void check_param_free(pixel **temp, int height, unsigned int param, 
					unsigned int min, unsigned int max);
void check_more_param(pixel **temp, int height, unsigned int min, 
		unsigned int start, unsigned int end, unsigned int max);
void error_initialise_argum();
void error_initialise_argum_free(pixel **temp, int height);
unsigned int get_param(int *param);