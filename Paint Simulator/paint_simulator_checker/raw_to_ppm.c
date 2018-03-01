#include <assert.h>
#include <stdio.h>
#include <string.h>

#define MAX_FILENAME_LEN 64

int main(int argc, char *argv[])
{
    /* It is also passed the current test number and the path to the output
     * directory. */
    assert(argc == 3);
    char ppm_file[MAX_FILENAME_LEN] = {0};

    for (int count = 0, width = 0, height = 0;
         scanf("%d%d", &width, &height) == 2; ++count) {
        sprintf(ppm_file, "%s/test%s-%d.out", argv[2], argv[1], count);

        FILE *ppm_out = fopen(ppm_file, "w");
        assert(ppm_out != NULL);

        fprintf(ppm_out, "P3\n%d %d\n255\n", width, height);
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < 3 * width; j += 3) {
                int r, g, b;
                assert(scanf("%d%d%d", &r, &g, &b) == 3);
                fprintf(ppm_out, "%d %d %d ", r, g, b);
            }
            fprintf(ppm_out, "\n");
        }
        assert(fclose(ppm_out) == 0);
    }

    return 0;
}
