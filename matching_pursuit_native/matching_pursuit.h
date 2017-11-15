//////////////////////////////////////////////////////////////////////////////
//
// INCLUDE SECTION
//

#ifndef CHY_MATCHING_PURSUIT_H
#define CHY_MATCHING_PURSUIT_H

#ifdef CHYMP_STATIC
#define CHYMP_DEF static
#else
#define CHYMP_DEF extern
#endif

#ifdef CHYMP_DEBUG
#include <stdio.h> // printf
#endif

#include <stdlib.h> // abs
#include <string.h> // memset
#include <math.h>   // pow
#include "../lib/TComTrQuant.cpp"

#ifdef __cplusplus
extern "C" {
#endif

CHYMP_DEF void chymp_matching_pursuit(int size,
                                      TCoeff *bb,
                                      int *mask,
                                      double ep,
                                      TCoeff *coeff,
                                      TCoeff *rec);
CHYMP_DEF void chymp_init(void);
CHYMP_DEF void chymp_free(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // CHY_MATCHING_PURSUIT_H

//////////////////////////////////////////////////////////////////////////////
//
// IMPLEMENTATION SECTION
//

#ifdef CHY_MATCHING_PURSUIT_IMPLEMENTATION

static TCoeff *basis4 = NULL;
static TCoeff *basis8 = NULL;
static TCoeff *basis16 = NULL;
static TCoeff *basis32 = NULL;

static void chymp__dct(TCoeff *input, TCoeff *output, int width, int height)
{
    xTrMxN(8, input, output, width, height, false, 15);
}

static void chymp__idct(TCoeff *input, TCoeff *output, int width, int height)
{
    xITrMxN(8, input, output, width, height, false, 15);
}

static void chymp__create_basis(int size, TCoeff *block)
{
    TCoeff input[1024];
    unsigned int i;
    unsigned int length = size * size;

    TCoeff *current_block = block;

    for (i = 0; i < length; i++)
    {
        memset(input, 0, sizeof(input));
        input[i] = 8192;
        chymp__idct(input, current_block, size, size);
        current_block += size * size;
    }
}

CHYMP_DEF void chymp_init(void)
{
    basis4 = (TCoeff *)malloc(4 * 4 * 4 * 4 * sizeof(TCoeff));
    basis8 = (TCoeff *)malloc(8 * 8 * 8 * 8 * sizeof(TCoeff));
    basis16 = (TCoeff *)malloc(16 * 16 * 16 * 16 * sizeof(TCoeff));
    basis32 = (TCoeff *)malloc(32 * 32 * 32 * 32 * sizeof(TCoeff));
    chymp__create_basis(4, basis4);
    chymp__create_basis(8, basis8);
    chymp__create_basis(16, basis16);
    chymp__create_basis(32, basis32);
}

CHYMP_DEF void chymp_free(void)
{
    free(basis4);
    free(basis8);
    free(basis16);
    free(basis32);
}

CHYMP_DEF void chymp_mask(int *pixels, UInt stride, int *mask)
{
    const UInt length = stride * stride;
    Double sum = 0.0;
    Double avg = 0.0;

    // calculate the average value for the block
    for (UInt i = 0; i < length; i++)
    {
        sum += *(pixels + i);
    }
    avg = sum / length;

    // classify the pixels as dark or light
    for (UInt i = 0; i < length; i++)
    {
        const UInt offsetX = i % stride;
        const UInt offsetY = i / stride;
        // calculate address of mask bit
        int *maskbit = mask + offsetX + offsetY * stride;
        if (*(pixels + i) > avg)
        {
            *maskbit = 1;
        }
        else
        {
            *maskbit = 0;
        }
    }
}

CHYMP_DEF void chymp_matching_pursuit(int size,
                                      TCoeff *bb,
                                      int *mask,
                                      double ep,
                                      TCoeff *coeff,
                                      TCoeff *rec)
{
    // Size of block
    unsigned int length = size * size;

    // Number of bits in mask
    unsigned int ml;

    // Mean square error
    double err;

    // Loop index
    unsigned int i, index;

    // Masked block
    TCoeff xt[1024];

    // Temporary block
    TCoeff tmp[1024];

    // Most significant coefficient
    TCoeff sigcoeff;

    // Output coefficients
    TCoeff *yt = coeff;

    // Basis functions
    TCoeff *basis, *basis_set;
    switch (size)
    {
    case 4:
        basis_set = basis4;
        break;
    case 8:
        basis_set = basis8;
        break;
    case 16:
        basis_set = basis16;
        break;
    case 32:
        basis_set = basis32;
        break;
    default:
        exit(1);
        break;
    }

    // Initialize inputs
    memset(yt, 0, size * size * sizeof(TCoeff));
    for (i = 0; i < length; i++)
    {
        xt[i] = bb[i] * mask[i];
    }
    ml = 0;
    for (i = 0; i < length; i++)
    {
        ml = ml + mask[i];
    }

    // Calculate mean square error
    err = 0;
    for (i = 0; i < length; i++)
    {
        err = err + (bb[i] * mask[i]) * (bb[i] * mask[i]);
    }
    err = err / ml;
#ifdef CHYMP_DEBUG
    printf("    err = %f\n", err);
    printf("- - - - - - - -\n");
#endif

    int tries = 0;
    while (err > ep && tries < 100)
    {
        tries++;
#ifdef CHYMP_DEBUG
        printf("  tries = %u\n", tries);
#endif

        // Find the most significant coefficient
        chymp__dct(xt, tmp, size, size);
        sigcoeff = INT32_MIN;
        for (i = 0; i < length; i++)
        {
            if (abs(tmp[i]) > sigcoeff)
            {
                index = i;
                sigcoeff = abs(tmp[i]);
            }
        }
        sigcoeff = tmp[index];
#ifdef CHYMP_DEBUG
        printf("     ix = %u\n", index);
        printf("maximum = %d\n", sigcoeff);
#endif

        // Subtract scaled basis from masked block
        basis = basis_set + index * size * size;
        for (i = 0; i < length; i++)
        {
            xt[i] -= sigcoeff * basis[i] * mask[i] / 8192;
        }

        // Reconstruct using the coefficients found so far
        coeff[index] += sigcoeff;
        chymp__idct(coeff, rec, size, size);

        // Recalculate error
        err = 0;
        for (i = 0; i < length; i++)
        {
            int diff = (rec[i] - bb[i]) * mask[i];
            err += diff * diff;
        }
        err /= ml;
#ifdef CHYMP_DEBUG
        printf("    err = %f\n", err);
        printf("- - - - - - - -\n");
#endif
    }
}

#endif
