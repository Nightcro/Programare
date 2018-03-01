void get_image(pixel **temp, int width, int height);
pixel **crop(pixel **temp, int height, int width, int start_col, 
			int start_line, int end_col, int end_line);
pixel **resize(pixel **temp, int height, int width, int h_res, int w_res);
void color_region(pixel **temp, int height, int width, int start_col, 
	int start_line, int end_col, int end_line, int red, int green, int blue);
pixel **blur(pixel **temp, int height, int width, int num_iter);
pixel **rotation(pixel **temp, int height, int width, int num_rot);
void fill(pixel **temp, int height, int width, int start_col, int start_line, 
		int red, int green, int blue);