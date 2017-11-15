#include <stdio.h>

#define CHY_MATCHING_PURSUIT_IMPLEMENTATION
#include "matching_pursuit.h"

int image[] = {219, 219, 219, 219, 219, 219, 219, 219,
               219, 219, 219, 219, 219, 219, 219, 219,
               18, 141, 216, 211, 38, 172, 216, 210,
               180, 28, 160, 160, 128, 196, 203, 198,
               202, 80, 128, 196, 36, 160, 200, 196,
               202, 80, 128, 195, 36, 159, 200, 195,
               176, 31, 182, 197, 54, 129, 199, 154,
               21, 157, 199, 201, 154, 17, 17, 51};

int mask[] = {0, 0, 0, 0, 0, 0, 0, 0,
              0, 0, 0, 0, 0, 0, 0, 0,
              1, 0, 0, 0, 1, 0, 0, 0,
              0, 1, 0, 0, 1, 0, 0, 0,
              0, 1, 0, 0, 1, 0, 0, 0,
              0, 1, 0, 0, 1, 0, 0, 0,
              0, 1, 0, 0, 1, 0, 0, 0,
              1, 0, 0, 0, 0, 1, 1, 1};

int main()
{
    unsigned int i;
    int coeff[64];
    int rec[64];
    int coeff2[64];
    int rec2[64];
    char filename[] = "love2d-visualize/output.lua";
    FILE *f;

    printf("Starting...\n");

    for (i = 0; i < 64; i++)
        image[i] -= 128;

    chymp_init();
    chymp_matching_pursuit(8, image, mask, 1000, coeff, rec);
    for (i = 0; i < 64; i++)
        mask[i] = -mask[i]+1;
    chymp_matching_pursuit(8, image, mask, 1000, coeff2, rec2);
    chymp_free();

    f = fopen(filename, "w");

    fprintf(f, "image = {");
    for (i = 0; i < 64; i++)
    {
        fprintf(f, "%d,", image[i]);
    }
    fprintf(f, "}\n");

    fprintf(f, "mask = {");
    for (i = 0; i < 64; i++)
    {
        fprintf(f, "%d,", mask[i]);
    }
    fprintf(f, "}\n");

    fprintf(f, "coeff = {");
    for (i = 0; i < 64; i++)
    {
        fprintf(f, "%d,", coeff[i]);
    }
    fprintf(f, "}\n");

    fprintf(f, "rec = {");
    for (i = 0; i < 64; i++)
    {
        fprintf(f, "%d,", rec[i]);
    }
    fprintf(f, "}\n");

    fprintf(f, "coeff2 = {");
    for (i = 0; i < 64; i++)
    {
        fprintf(f, "%d,", coeff2[i]);
    }
    fprintf(f, "}\n");

    fprintf(f, "rec2 = {");
    for (i = 0; i < 64; i++)
    {
        fprintf(f, "%d,", rec2[i]);
    }
    fprintf(f, "}\n");
    fclose(f);

    return 0;
}
