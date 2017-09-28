#include "CommonDef.h"

#define DEFINE_DST4x4_MATRIX(a,b,c,d) \
{ \
  {  a,  b,  c,  d }, \
  {  c,  c,  0, -c }, \
  {  d, -a, -c,  b }, \
  {  b, -d,  c, -a }, \
}

#define DEFINE_DCT4x4_MATRIX(a,b,c) \
{ \
  { a,  a,  a,  a}, \
  { b,  c, -c, -b}, \
  { a, -a, -a,  a}, \
  { c, -b,  b, -c}  \
}

#define DEFINE_DCT8x8_MATRIX(a,b,c,d,e,f,g) \
{ \
  { a,  a,  a,  a,  a,  a,  a,  a}, \
  { d,  e,  f,  g, -g, -f, -e, -d}, \
  { b,  c, -c, -b, -b, -c,  c,  b}, \
  { e, -g, -d, -f,  f,  d,  g, -e}, \
  { a, -a, -a,  a,  a, -a, -a,  a}, \
  { f, -d,  g,  e, -e, -g,  d, -f}, \
  { c, -b,  b, -c, -c,  b, -b,  c}, \
  { g, -f,  e, -d,  d, -e,  f, -g}  \
}

#define DEFINE_DCT16x16_MATRIX(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o) \
{ \
  { a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a}, \
  { h,  i,  j,  k,  l,  m,  n,  o, -o, -n, -m, -l, -k, -j, -i, -h}, \
  { d,  e,  f,  g, -g, -f, -e, -d, -d, -e, -f, -g,  g,  f,  e,  d}, \
  { i,  l,  o, -m, -j, -h, -k, -n,  n,  k,  h,  j,  m, -o, -l, -i}, \
  { b,  c, -c, -b, -b, -c,  c,  b,  b,  c, -c, -b, -b, -c,  c,  b}, \
  { j,  o, -k, -i, -n,  l,  h,  m, -m, -h, -l,  n,  i,  k, -o, -j}, \
  { e, -g, -d, -f,  f,  d,  g, -e, -e,  g,  d,  f, -f, -d, -g,  e}, \
  { k, -m, -i,  o,  h,  n, -j, -l,  l,  j, -n, -h, -o,  i,  m, -k}, \
  { a, -a, -a,  a,  a, -a, -a,  a,  a, -a, -a,  a,  a, -a, -a,  a}, \
  { l, -j, -n,  h, -o, -i,  m,  k, -k, -m,  i,  o, -h,  n,  j, -l}, \
  { f, -d,  g,  e, -e, -g,  d, -f, -f,  d, -g, -e,  e,  g, -d,  f}, \
  { m, -h,  l,  n, -i,  k,  o, -j,  j, -o, -k,  i, -n, -l,  h, -m}, \
  { c, -b,  b, -c, -c,  b, -b,  c,  c, -b,  b, -c, -c,  b, -b,  c}, \
  { n, -k,  h, -j,  m,  o, -l,  i, -i,  l, -o, -m,  j, -h,  k, -n}, \
  { g, -f,  e, -d,  d, -e,  f, -g, -g,  f, -e,  d, -d,  e, -f,  g}, \
  { o, -n,  m, -l,  k, -j,  i, -h,  h, -i,  j, -k,  l, -m,  n, -o}  \
}

#define DEFINE_DCT32x32_MATRIX(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,A,B,C,D,E) \
{ \
  { a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a,  a}, \
  { p,  q,  r,  s,  t,  u,  v,  w,  x,  y,  z,  A,  B,  C,  D,  E, -E, -D, -C, -B, -A, -z, -y, -x, -w, -v, -u, -t, -s, -r, -q, -p}, \
  { h,  i,  j,  k,  l,  m,  n,  o, -o, -n, -m, -l, -k, -j, -i, -h, -h, -i, -j, -k, -l, -m, -n, -o,  o,  n,  m,  l,  k,  j,  i,  h}, \
  { q,  t,  w,  z,  C, -E, -B, -y, -v, -s, -p, -r, -u, -x, -A, -D,  D,  A,  x,  u,  r,  p,  s,  v,  y,  B,  E, -C, -z, -w, -t, -q}, \
  { d,  e,  f,  g, -g, -f, -e, -d, -d, -e, -f, -g,  g,  f,  e,  d,  d,  e,  f,  g, -g, -f, -e, -d, -d, -e, -f, -g,  g,  f,  e,  d}, \
  { r,  w,  B, -D, -y, -t, -p, -u, -z, -E,  A,  v,  q,  s,  x,  C, -C, -x, -s, -q, -v, -A,  E,  z,  u,  p,  t,  y,  D, -B, -w, -r}, \
  { i,  l,  o, -m, -j, -h, -k, -n,  n,  k,  h,  j,  m, -o, -l, -i, -i, -l, -o,  m,  j,  h,  k,  n, -n, -k, -h, -j, -m,  o,  l,  i}, \
  { s,  z, -D, -w, -p, -v, -C,  A,  t,  r,  y, -E, -x, -q, -u, -B,  B,  u,  q,  x,  E, -y, -r, -t, -A,  C,  v,  p,  w,  D, -z, -s}, \
  { b,  c, -c, -b, -b, -c,  c,  b,  b,  c, -c, -b, -b, -c,  c,  b,  b,  c, -c, -b, -b, -c,  c,  b,  b,  c, -c, -b, -b, -c,  c,  b}, \
  { t,  C, -y, -p, -x,  D,  u,  s,  B, -z, -q, -w,  E,  v,  r,  A, -A, -r, -v, -E,  w,  q,  z, -B, -s, -u, -D,  x,  p,  y, -C, -t}, \
  { j,  o, -k, -i, -n,  l,  h,  m, -m, -h, -l,  n,  i,  k, -o, -j, -j, -o,  k,  i,  n, -l, -h, -m,  m,  h,  l, -n, -i, -k,  o,  j}, \
  { u, -E, -t, -v,  D,  s,  w, -C, -r, -x,  B,  q,  y, -A, -p, -z,  z,  p,  A, -y, -q, -B,  x,  r,  C, -w, -s, -D,  v,  t,  E, -u}, \
  { e, -g, -d, -f,  f,  d,  g, -e, -e,  g,  d,  f, -f, -d, -g,  e,  e, -g, -d, -f,  f,  d,  g, -e, -e,  g,  d,  f, -f, -d, -g,  e}, \
  { v, -B, -p, -C,  u,  w, -A, -q, -D,  t,  x, -z, -r, -E,  s,  y, -y, -s,  E,  r,  z, -x, -t,  D,  q,  A, -w, -u,  C,  p,  B, -v}, \
  { k, -m, -i,  o,  h,  n, -j, -l,  l,  j, -n, -h, -o,  i,  m, -k, -k,  m,  i, -o, -h, -n,  j,  l, -l, -j,  n,  h,  o, -i, -m,  k}, \
  { w, -y, -u,  A,  s, -C, -q,  E,  p,  D, -r, -B,  t,  z, -v, -x,  x,  v, -z, -t,  B,  r, -D, -p, -E,  q,  C, -s, -A,  u,  y, -w}, \
  { a, -a, -a,  a,  a, -a, -a,  a,  a, -a, -a,  a,  a, -a, -a,  a,  a, -a, -a,  a,  a, -a, -a,  a,  a, -a, -a,  a,  a, -a, -a,  a}, \
  { x, -v, -z,  t,  B, -r, -D,  p, -E, -q,  C,  s, -A, -u,  y,  w, -w, -y,  u,  A, -s, -C,  q,  E, -p,  D,  r, -B, -t,  z,  v, -x}, \
  { l, -j, -n,  h, -o, -i,  m,  k, -k, -m,  i,  o, -h,  n,  j, -l, -l,  j,  n, -h,  o,  i, -m, -k,  k,  m, -i, -o,  h, -n, -j,  l}, \
  { y, -s, -E,  r, -z, -x,  t,  D, -q,  A,  w, -u, -C,  p, -B, -v,  v,  B, -p,  C,  u, -w, -A,  q, -D, -t,  x,  z, -r,  E,  s, -y}, \
  { f, -d,  g,  e, -e, -g,  d, -f, -f,  d, -g, -e,  e,  g, -d,  f,  f, -d,  g,  e, -e, -g,  d, -f, -f,  d, -g, -e,  e,  g, -d,  f}, \
  { z, -p,  A,  y, -q,  B,  x, -r,  C,  w, -s,  D,  v, -t,  E,  u, -u, -E,  t, -v, -D,  s, -w, -C,  r, -x, -B,  q, -y, -A,  p, -z}, \
  { m, -h,  l,  n, -i,  k,  o, -j,  j, -o, -k,  i, -n, -l,  h, -m, -m,  h, -l, -n,  i, -k, -o,  j, -j,  o,  k, -i,  n,  l, -h,  m}, \
  { A, -r,  v, -E, -w,  q, -z, -B,  s, -u,  D,  x, -p,  y,  C, -t,  t, -C, -y,  p, -x, -D,  u, -s,  B,  z, -q,  w,  E, -v,  r, -A}, \
  { c, -b,  b, -c, -c,  b, -b,  c,  c, -b,  b, -c, -c,  b, -b,  c,  c, -b,  b, -c, -c,  b, -b,  c,  c, -b,  b, -c, -c,  b, -b,  c}, \
  { B, -u,  q, -x,  E,  y, -r,  t, -A, -C,  v, -p,  w, -D, -z,  s, -s,  z,  D, -w,  p, -v,  C,  A, -t,  r, -y, -E,  x, -q,  u, -B}, \
  { n, -k,  h, -j,  m,  o, -l,  i, -i,  l, -o, -m,  j, -h,  k, -n, -n,  k, -h,  j, -m, -o,  l, -i,  i, -l,  o,  m, -j,  h, -k,  n}, \
  { C, -x,  s, -q,  v, -A, -E,  z, -u,  p, -t,  y, -D, -B,  w, -r,  r, -w,  B,  D, -y,  t, -p,  u, -z,  E,  A, -v,  q, -s,  x, -C}, \
  { g, -f,  e, -d,  d, -e,  f, -g, -g,  f, -e,  d, -d,  e, -f,  g,  g, -f,  e, -d,  d, -e,  f, -g, -g,  f, -e,  d, -d,  e, -f,  g}, \
  { D, -A,  x, -u,  r, -p,  s, -v,  y, -B,  E,  C, -z,  w, -t,  q, -q,  t, -w,  z, -C, -E,  B, -y,  v, -s,  p, -r,  u, -x,  A, -D}, \
  { o, -n,  m, -l,  k, -j,  i, -h,  h, -i,  j, -k,  l, -m,  n, -o, -o,  n, -m,  l, -k,  j, -i,  h, -h,  i, -j,  k, -l,  m, -n,  o}, \
  { E, -D,  C, -B,  A, -z,  y, -x,  w, -v,  u, -t,  s, -r,  q, -p,  p, -q,  r, -s,  t, -u,  v, -w,  x, -y,  z, -A,  B, -C,  D, -E}  \
}

static const Int g_transformMatrixShift[TRANSFORM_NUMBER_OF_DIRECTIONS] = {  6, 6 };
static const SChar  g_aucConvertToBit[65] = {
  -1,
  -1, -1, -1, 0,
  -1, -1, -1, 1,
  -1, -1, -1, -1, -1, -1, -1, 2,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 3,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4
};

const TMatrixCoeff g_aiT4 [TRANSFORM_NUMBER_OF_DIRECTIONS][4][4]   =
{
  DEFINE_DCT4x4_MATRIX  (   64,    83,    36),
  DEFINE_DCT4x4_MATRIX  (   64,    83,    36)
};

const TMatrixCoeff g_aiT8 [TRANSFORM_NUMBER_OF_DIRECTIONS][8][8]   =
{
  DEFINE_DCT8x8_MATRIX  (   64,    83,    36,    89,    75,    50,    18),
  DEFINE_DCT8x8_MATRIX  (   64,    83,    36,    89,    75,    50,    18)
};

const TMatrixCoeff g_aiT16[TRANSFORM_NUMBER_OF_DIRECTIONS][16][16] =
{
  DEFINE_DCT16x16_MATRIX(   64,    83,    36,    89,    75,    50,    18,    90,    87,    80,    70,    57,    43,    25,     9),
  DEFINE_DCT16x16_MATRIX(   64,    83,    36,    89,    75,    50,    18,    90,    87,    80,    70,    57,    43,    25,     9)
};

const TMatrixCoeff g_aiT32[TRANSFORM_NUMBER_OF_DIRECTIONS][32][32] =
{
  DEFINE_DCT32x32_MATRIX(   64,    83,    36,    89,    75,    50,    18,    90,    87,    80,    70,    57,    43,    25,     9,    90,    90,    88,    85,    82,    78,    73,    67,    61,    54,    46,    38,    31,    22,    13,     4),
  DEFINE_DCT32x32_MATRIX(   64,    83,    36,    89,    75,    50,    18,    90,    87,    80,    70,    57,    43,    25,     9,    90,    90,    88,    85,    82,    78,    73,    67,    61,    54,    46,    38,    31,    22,    13,     4)
};

const TMatrixCoeff g_as_DST_MAT_4[TRANSFORM_NUMBER_OF_DIRECTIONS][4][4] =
{
  DEFINE_DST4x4_MATRIX(   29,    55,    74,    84),
  DEFINE_DST4x4_MATRIX(   29,    55,    74,    84)
};

extern "C" {

/** 4x4 forward transform implemented using partial butterfly structure (1D)
 *  \param src   input data (residual)
 *  \param dst   output data (transform coefficients)
 *  \param shift specifies right shift after 1D transform
 *  \param line
 */
Void partialButterfly4(TCoeff *src, TCoeff *dst, Int shift, Int line)
{
  Int j;
  TCoeff E[2],O[2];
  TCoeff add = (shift > 0) ? (1<<(shift-1)) : 0;

  for (j=0; j<line; j++)
  {
    /* E and O */
    E[0] = src[0] + src[3];
    O[0] = src[0] - src[3];
    E[1] = src[1] + src[2];
    O[1] = src[1] - src[2];

    dst[0]      = (g_aiT4[TRANSFORM_FORWARD][0][0]*E[0] + g_aiT4[TRANSFORM_FORWARD][0][1]*E[1] + add)>>shift;
    dst[2*line] = (g_aiT4[TRANSFORM_FORWARD][2][0]*E[0] + g_aiT4[TRANSFORM_FORWARD][2][1]*E[1] + add)>>shift;
    dst[line]   = (g_aiT4[TRANSFORM_FORWARD][1][0]*O[0] + g_aiT4[TRANSFORM_FORWARD][1][1]*O[1] + add)>>shift;
    dst[3*line] = (g_aiT4[TRANSFORM_FORWARD][3][0]*O[0] + g_aiT4[TRANSFORM_FORWARD][3][1]*O[1] + add)>>shift;

    src += 4;
    dst ++;
  }
}

// Fast DST Algorithm. Full matrix multiplication for DST and Fast DST algorithm
// give identical results
Void fastForwardDst(TCoeff *block, TCoeff *coeff, Int shift)  // input block, output coeff
{
  Int i;
  TCoeff c[4];
  TCoeff rnd_factor = (shift > 0) ? (1<<(shift-1)) : 0;
  for (i=0; i<4; i++)
  {
    // Intermediate Variables
    c[0] = block[4*i+0];
    c[1] = block[4*i+1];
    c[2] = block[4*i+2];
    c[3] = block[4*i+3];

    for (Int row = 0; row < 4; row++)
    {
      TCoeff result = 0;
      for (Int column = 0; column < 4; column++)
      {
        result += c[column] * g_as_DST_MAT_4[TRANSFORM_FORWARD][row][column]; // use the defined matrix, rather than hard-wired numbers
      }

      coeff[(row * 4) + i] = rightShift((result + rnd_factor), shift);
    }
  }
}

Void fastInverseDst(TCoeff *tmp, TCoeff *block, Int shift, const TCoeff outputMinimum, const TCoeff outputMaximum)  // input tmp, output block
{
  Int i;
  TCoeff c[4];
  TCoeff rnd_factor = (shift > 0) ? (1<<(shift-1)) : 0;
  for (i=0; i<4; i++)
  {
    // Intermediate Variables
    c[0] = tmp[   i];
    c[1] = tmp[4 +i];
    c[2] = tmp[8 +i];
    c[3] = tmp[12+i];

    for (Int column = 0; column < 4; column++)
    {
      TCoeff &result = block[(i * 4) + column];

      result = 0;
      for (Int row = 0; row < 4; row++)
      {
        result += c[row] * g_as_DST_MAT_4[TRANSFORM_INVERSE][row][column]; // use the defined matrix, rather than hard-wired numbers
      }

      result = Clip3( outputMinimum, outputMaximum, rightShift((result + rnd_factor), shift));
    }
  }
}

/** 4x4 inverse transform implemented using partial butterfly structure (1D)
 *  \param src   input data (transform coefficients)
 *  \param dst   output data (residual)
 *  \param shift specifies right shift after 1D transform
 *  \param line
 *  \param outputMinimum  minimum for clipping
 *  \param outputMaximum  maximum for clipping
 */
Void partialButterflyInverse4(TCoeff *src, TCoeff *dst, Int shift, Int line, const TCoeff outputMinimum, const TCoeff outputMaximum)
{
  Int j;
  TCoeff E[2],O[2];
  TCoeff add = (shift > 0) ? (1<<(shift-1)) : 0;

  for (j=0; j<line; j++)
  {
    /* Utilizing symmetry properties to the maximum to minimize the number of multiplications */
    O[0] = g_aiT4[TRANSFORM_INVERSE][1][0]*src[line] + g_aiT4[TRANSFORM_INVERSE][3][0]*src[3*line];
    O[1] = g_aiT4[TRANSFORM_INVERSE][1][1]*src[line] + g_aiT4[TRANSFORM_INVERSE][3][1]*src[3*line];
    E[0] = g_aiT4[TRANSFORM_INVERSE][0][0]*src[0]    + g_aiT4[TRANSFORM_INVERSE][2][0]*src[2*line];
    E[1] = g_aiT4[TRANSFORM_INVERSE][0][1]*src[0]    + g_aiT4[TRANSFORM_INVERSE][2][1]*src[2*line];

    /* Combining even and odd terms at each hierarchy levels to calculate the final spatial domain vector */
    dst[0] = Clip3( outputMinimum, outputMaximum, (E[0] + O[0] + add)>>shift );
    dst[1] = Clip3( outputMinimum, outputMaximum, (E[1] + O[1] + add)>>shift );
    dst[2] = Clip3( outputMinimum, outputMaximum, (E[1] - O[1] + add)>>shift );
    dst[3] = Clip3( outputMinimum, outputMaximum, (E[0] - O[0] + add)>>shift );

    src   ++;
    dst += 4;
  }
}

/** 8x8 forward transform implemented using partial butterfly structure (1D)
 *  \param src   input data (residual)
 *  \param dst   output data (transform coefficients)
 *  \param shift specifies right shift after 1D transform
 *  \param line
 */
Void partialButterfly8(TCoeff *src, TCoeff *dst, Int shift, Int line)
{
  Int j,k;
  TCoeff E[4],O[4];
  TCoeff EE[2],EO[2];
  TCoeff add = (shift > 0) ? (1<<(shift-1)) : 0;

  for (j=0; j<line; j++)
  {
    /* E and O*/
    for (k=0;k<4;k++)
    {
      E[k] = src[k] + src[7-k];
      O[k] = src[k] - src[7-k];
    }
    /* EE and EO */
    EE[0] = E[0] + E[3];
    EO[0] = E[0] - E[3];
    EE[1] = E[1] + E[2];
    EO[1] = E[1] - E[2];

    dst[0]      = (g_aiT8[TRANSFORM_FORWARD][0][0]*EE[0] + g_aiT8[TRANSFORM_FORWARD][0][1]*EE[1] + add)>>shift;
    dst[4*line] = (g_aiT8[TRANSFORM_FORWARD][4][0]*EE[0] + g_aiT8[TRANSFORM_FORWARD][4][1]*EE[1] + add)>>shift;
    dst[2*line] = (g_aiT8[TRANSFORM_FORWARD][2][0]*EO[0] + g_aiT8[TRANSFORM_FORWARD][2][1]*EO[1] + add)>>shift;
    dst[6*line] = (g_aiT8[TRANSFORM_FORWARD][6][0]*EO[0] + g_aiT8[TRANSFORM_FORWARD][6][1]*EO[1] + add)>>shift;

    dst[line]   = (g_aiT8[TRANSFORM_FORWARD][1][0]*O[0] + g_aiT8[TRANSFORM_FORWARD][1][1]*O[1] + g_aiT8[TRANSFORM_FORWARD][1][2]*O[2] + g_aiT8[TRANSFORM_FORWARD][1][3]*O[3] + add)>>shift;
    dst[3*line] = (g_aiT8[TRANSFORM_FORWARD][3][0]*O[0] + g_aiT8[TRANSFORM_FORWARD][3][1]*O[1] + g_aiT8[TRANSFORM_FORWARD][3][2]*O[2] + g_aiT8[TRANSFORM_FORWARD][3][3]*O[3] + add)>>shift;
    dst[5*line] = (g_aiT8[TRANSFORM_FORWARD][5][0]*O[0] + g_aiT8[TRANSFORM_FORWARD][5][1]*O[1] + g_aiT8[TRANSFORM_FORWARD][5][2]*O[2] + g_aiT8[TRANSFORM_FORWARD][5][3]*O[3] + add)>>shift;
    dst[7*line] = (g_aiT8[TRANSFORM_FORWARD][7][0]*O[0] + g_aiT8[TRANSFORM_FORWARD][7][1]*O[1] + g_aiT8[TRANSFORM_FORWARD][7][2]*O[2] + g_aiT8[TRANSFORM_FORWARD][7][3]*O[3] + add)>>shift;

    src += 8;
    dst ++;
  }
}

/** 8x8 inverse transform implemented using partial butterfly structure (1D)
 *  \param src   input data (transform coefficients)
 *  \param dst   output data (residual)
 *  \param shift specifies right shift after 1D transform
 *  \param line
 *  \param outputMinimum  minimum for clipping
 *  \param outputMaximum  maximum for clipping
 */
Void partialButterflyInverse8(TCoeff *src, TCoeff *dst, Int shift, Int line, const TCoeff outputMinimum, const TCoeff outputMaximum)
{
  Int j,k;
  TCoeff E[4],O[4];
  TCoeff EE[2],EO[2];
  TCoeff add = (shift > 0) ? (1<<(shift-1)) : 0;

  for (j=0; j<line; j++)
  {
    /* Utilizing symmetry properties to the maximum to minimize the number of multiplications */
    for (k=0;k<4;k++)
    {
      O[k] = g_aiT8[TRANSFORM_INVERSE][ 1][k]*src[line]   + g_aiT8[TRANSFORM_INVERSE][ 3][k]*src[3*line] +
             g_aiT8[TRANSFORM_INVERSE][ 5][k]*src[5*line] + g_aiT8[TRANSFORM_INVERSE][ 7][k]*src[7*line];
    }

    EO[0] = g_aiT8[TRANSFORM_INVERSE][2][0]*src[ 2*line ] + g_aiT8[TRANSFORM_INVERSE][6][0]*src[ 6*line ];
    EO[1] = g_aiT8[TRANSFORM_INVERSE][2][1]*src[ 2*line ] + g_aiT8[TRANSFORM_INVERSE][6][1]*src[ 6*line ];
    EE[0] = g_aiT8[TRANSFORM_INVERSE][0][0]*src[ 0      ] + g_aiT8[TRANSFORM_INVERSE][4][0]*src[ 4*line ];
    EE[1] = g_aiT8[TRANSFORM_INVERSE][0][1]*src[ 0      ] + g_aiT8[TRANSFORM_INVERSE][4][1]*src[ 4*line ];

    /* Combining even and odd terms at each hierarchy levels to calculate the final spatial domain vector */
    E[0] = EE[0] + EO[0];
    E[3] = EE[0] - EO[0];
    E[1] = EE[1] + EO[1];
    E[2] = EE[1] - EO[1];
    for (k=0;k<4;k++)
    {
      dst[ k   ] = Clip3( outputMinimum, outputMaximum, (E[k] + O[k] + add)>>shift );
      dst[ k+4 ] = Clip3( outputMinimum, outputMaximum, (E[3-k] - O[3-k] + add)>>shift );
    }
    src ++;
    dst += 8;
  }
}

/** 16x16 forward transform implemented using partial butterfly structure (1D)
 *  \param src   input data (residual)
 *  \param dst   output data (transform coefficients)
 *  \param shift specifies right shift after 1D transform
 *  \param line
 */
Void partialButterfly16(TCoeff *src, TCoeff *dst, Int shift, Int line)
{
  Int j,k;
  TCoeff E[8],O[8];
  TCoeff EE[4],EO[4];
  TCoeff EEE[2],EEO[2];
  TCoeff add = (shift > 0) ? (1<<(shift-1)) : 0;

  for (j=0; j<line; j++)
  {
    /* E and O*/
    for (k=0;k<8;k++)
    {
      E[k] = src[k] + src[15-k];
      O[k] = src[k] - src[15-k];
    }
    /* EE and EO */
    for (k=0;k<4;k++)
    {
      EE[k] = E[k] + E[7-k];
      EO[k] = E[k] - E[7-k];
    }
    /* EEE and EEO */
    EEE[0] = EE[0] + EE[3];
    EEO[0] = EE[0] - EE[3];
    EEE[1] = EE[1] + EE[2];
    EEO[1] = EE[1] - EE[2];

    dst[ 0      ] = (g_aiT16[TRANSFORM_FORWARD][ 0][0]*EEE[0] + g_aiT16[TRANSFORM_FORWARD][ 0][1]*EEE[1] + add)>>shift;
    dst[ 8*line ] = (g_aiT16[TRANSFORM_FORWARD][ 8][0]*EEE[0] + g_aiT16[TRANSFORM_FORWARD][ 8][1]*EEE[1] + add)>>shift;
    dst[ 4*line ] = (g_aiT16[TRANSFORM_FORWARD][ 4][0]*EEO[0] + g_aiT16[TRANSFORM_FORWARD][ 4][1]*EEO[1] + add)>>shift;
    dst[ 12*line] = (g_aiT16[TRANSFORM_FORWARD][12][0]*EEO[0] + g_aiT16[TRANSFORM_FORWARD][12][1]*EEO[1] + add)>>shift;

    for (k=2;k<16;k+=4)
    {
      dst[ k*line ] = (g_aiT16[TRANSFORM_FORWARD][k][0]*EO[0] + g_aiT16[TRANSFORM_FORWARD][k][1]*EO[1] +
                       g_aiT16[TRANSFORM_FORWARD][k][2]*EO[2] + g_aiT16[TRANSFORM_FORWARD][k][3]*EO[3] + add)>>shift;
    }

    for (k=1;k<16;k+=2)
    {
      dst[ k*line ] = (g_aiT16[TRANSFORM_FORWARD][k][0]*O[0] + g_aiT16[TRANSFORM_FORWARD][k][1]*O[1] +
                       g_aiT16[TRANSFORM_FORWARD][k][2]*O[2] + g_aiT16[TRANSFORM_FORWARD][k][3]*O[3] +
                       g_aiT16[TRANSFORM_FORWARD][k][4]*O[4] + g_aiT16[TRANSFORM_FORWARD][k][5]*O[5] +
                       g_aiT16[TRANSFORM_FORWARD][k][6]*O[6] + g_aiT16[TRANSFORM_FORWARD][k][7]*O[7] + add)>>shift;
    }

    src += 16;
    dst ++;

  }
}

/** 16x16 inverse transform implemented using partial butterfly structure (1D)
 *  \param src            input data (transform coefficients)
 *  \param dst            output data (residual)
 *  \param shift          specifies right shift after 1D transform
 *  \param line
 *  \param outputMinimum  minimum for clipping
 *  \param outputMaximum  maximum for clipping
 */
Void partialButterflyInverse16(TCoeff *src, TCoeff *dst, Int shift, Int line, const TCoeff outputMinimum, const TCoeff outputMaximum)
{
  Int j,k;
  TCoeff E[8],O[8];
  TCoeff EE[4],EO[4];
  TCoeff EEE[2],EEO[2];
  TCoeff add = (shift > 0) ? (1<<(shift-1)) : 0;

  for (j=0; j<line; j++)
  {
    /* Utilizing symmetry properties to the maximum to minimize the number of multiplications */
    for (k=0;k<8;k++)
    {
      O[k] = g_aiT16[TRANSFORM_INVERSE][ 1][k]*src[ line]   + g_aiT16[TRANSFORM_INVERSE][ 3][k]*src[ 3*line] +
             g_aiT16[TRANSFORM_INVERSE][ 5][k]*src[ 5*line] + g_aiT16[TRANSFORM_INVERSE][ 7][k]*src[ 7*line] +
             g_aiT16[TRANSFORM_INVERSE][ 9][k]*src[ 9*line] + g_aiT16[TRANSFORM_INVERSE][11][k]*src[11*line] +
             g_aiT16[TRANSFORM_INVERSE][13][k]*src[13*line] + g_aiT16[TRANSFORM_INVERSE][15][k]*src[15*line];
    }
    for (k=0;k<4;k++)
    {
      EO[k] = g_aiT16[TRANSFORM_INVERSE][ 2][k]*src[ 2*line] + g_aiT16[TRANSFORM_INVERSE][ 6][k]*src[ 6*line] +
              g_aiT16[TRANSFORM_INVERSE][10][k]*src[10*line] + g_aiT16[TRANSFORM_INVERSE][14][k]*src[14*line];
    }
    EEO[0] = g_aiT16[TRANSFORM_INVERSE][4][0]*src[ 4*line ] + g_aiT16[TRANSFORM_INVERSE][12][0]*src[ 12*line ];
    EEE[0] = g_aiT16[TRANSFORM_INVERSE][0][0]*src[ 0      ] + g_aiT16[TRANSFORM_INVERSE][ 8][0]*src[ 8*line  ];
    EEO[1] = g_aiT16[TRANSFORM_INVERSE][4][1]*src[ 4*line ] + g_aiT16[TRANSFORM_INVERSE][12][1]*src[ 12*line ];
    EEE[1] = g_aiT16[TRANSFORM_INVERSE][0][1]*src[ 0      ] + g_aiT16[TRANSFORM_INVERSE][ 8][1]*src[ 8*line  ];

    /* Combining even and odd terms at each hierarchy levels to calculate the final spatial domain vector */
    for (k=0;k<2;k++)
    {
      EE[k] = EEE[k] + EEO[k];
      EE[k+2] = EEE[1-k] - EEO[1-k];
    }
    for (k=0;k<4;k++)
    {
      E[k] = EE[k] + EO[k];
      E[k+4] = EE[3-k] - EO[3-k];
    }
    for (k=0;k<8;k++)
    {
      dst[k]   = Clip3( outputMinimum, outputMaximum, (E[k] + O[k] + add)>>shift );
      dst[k+8] = Clip3( outputMinimum, outputMaximum, (E[7-k] - O[7-k] + add)>>shift );
    }
    src ++;
    dst += 16;
  }
}

/** 32x32 forward transform implemented using partial butterfly structure (1D)
 *  \param src   input data (residual)
 *  \param dst   output data (transform coefficients)
 *  \param shift specifies right shift after 1D transform
 *  \param line
 */
Void partialButterfly32(TCoeff *src, TCoeff *dst, Int shift, Int line)
{
  Int j,k;
  TCoeff E[16],O[16];
  TCoeff EE[8],EO[8];
  TCoeff EEE[4],EEO[4];
  TCoeff EEEE[2],EEEO[2];
  TCoeff add = (shift > 0) ? (1<<(shift-1)) : 0;

  for (j=0; j<line; j++)
  {
    /* E and O*/
    for (k=0;k<16;k++)
    {
      E[k] = src[k] + src[31-k];
      O[k] = src[k] - src[31-k];
    }
    /* EE and EO */
    for (k=0;k<8;k++)
    {
      EE[k] = E[k] + E[15-k];
      EO[k] = E[k] - E[15-k];
    }
    /* EEE and EEO */
    for (k=0;k<4;k++)
    {
      EEE[k] = EE[k] + EE[7-k];
      EEO[k] = EE[k] - EE[7-k];
    }
    /* EEEE and EEEO */
    EEEE[0] = EEE[0] + EEE[3];
    EEEO[0] = EEE[0] - EEE[3];
    EEEE[1] = EEE[1] + EEE[2];
    EEEO[1] = EEE[1] - EEE[2];

    dst[ 0       ] = (g_aiT32[TRANSFORM_FORWARD][ 0][0]*EEEE[0] + g_aiT32[TRANSFORM_FORWARD][ 0][1]*EEEE[1] + add)>>shift;
    dst[ 16*line ] = (g_aiT32[TRANSFORM_FORWARD][16][0]*EEEE[0] + g_aiT32[TRANSFORM_FORWARD][16][1]*EEEE[1] + add)>>shift;
    dst[ 8*line  ] = (g_aiT32[TRANSFORM_FORWARD][ 8][0]*EEEO[0] + g_aiT32[TRANSFORM_FORWARD][ 8][1]*EEEO[1] + add)>>shift;
    dst[ 24*line ] = (g_aiT32[TRANSFORM_FORWARD][24][0]*EEEO[0] + g_aiT32[TRANSFORM_FORWARD][24][1]*EEEO[1] + add)>>shift;
    for (k=4;k<32;k+=8)
    {
      dst[ k*line ] = (g_aiT32[TRANSFORM_FORWARD][k][0]*EEO[0] + g_aiT32[TRANSFORM_FORWARD][k][1]*EEO[1] +
                       g_aiT32[TRANSFORM_FORWARD][k][2]*EEO[2] + g_aiT32[TRANSFORM_FORWARD][k][3]*EEO[3] + add)>>shift;
    }
    for (k=2;k<32;k+=4)
    {
      dst[ k*line ] = (g_aiT32[TRANSFORM_FORWARD][k][0]*EO[0] + g_aiT32[TRANSFORM_FORWARD][k][1]*EO[1] +
                       g_aiT32[TRANSFORM_FORWARD][k][2]*EO[2] + g_aiT32[TRANSFORM_FORWARD][k][3]*EO[3] +
                       g_aiT32[TRANSFORM_FORWARD][k][4]*EO[4] + g_aiT32[TRANSFORM_FORWARD][k][5]*EO[5] +
                       g_aiT32[TRANSFORM_FORWARD][k][6]*EO[6] + g_aiT32[TRANSFORM_FORWARD][k][7]*EO[7] + add)>>shift;
    }
    for (k=1;k<32;k+=2)
    {
      dst[ k*line ] = (g_aiT32[TRANSFORM_FORWARD][k][ 0]*O[ 0] + g_aiT32[TRANSFORM_FORWARD][k][ 1]*O[ 1] +
                       g_aiT32[TRANSFORM_FORWARD][k][ 2]*O[ 2] + g_aiT32[TRANSFORM_FORWARD][k][ 3]*O[ 3] +
                       g_aiT32[TRANSFORM_FORWARD][k][ 4]*O[ 4] + g_aiT32[TRANSFORM_FORWARD][k][ 5]*O[ 5] +
                       g_aiT32[TRANSFORM_FORWARD][k][ 6]*O[ 6] + g_aiT32[TRANSFORM_FORWARD][k][ 7]*O[ 7] +
                       g_aiT32[TRANSFORM_FORWARD][k][ 8]*O[ 8] + g_aiT32[TRANSFORM_FORWARD][k][ 9]*O[ 9] +
                       g_aiT32[TRANSFORM_FORWARD][k][10]*O[10] + g_aiT32[TRANSFORM_FORWARD][k][11]*O[11] +
                       g_aiT32[TRANSFORM_FORWARD][k][12]*O[12] + g_aiT32[TRANSFORM_FORWARD][k][13]*O[13] +
                       g_aiT32[TRANSFORM_FORWARD][k][14]*O[14] + g_aiT32[TRANSFORM_FORWARD][k][15]*O[15] + add)>>shift;
    }

    src += 32;
    dst ++;
  }
}

/** 32x32 inverse transform implemented using partial butterfly structure (1D)
 *  \param src   input data (transform coefficients)
 *  \param dst   output data (residual)
 *  \param shift specifies right shift after 1D transform
 *  \param line
 *  \param outputMinimum  minimum for clipping
 *  \param outputMaximum  maximum for clipping
 */
Void partialButterflyInverse32(TCoeff *src, TCoeff *dst, Int shift, Int line, const TCoeff outputMinimum, const TCoeff outputMaximum)
{
  Int j,k;
  TCoeff E[16],O[16];
  TCoeff EE[8],EO[8];
  TCoeff EEE[4],EEO[4];
  TCoeff EEEE[2],EEEO[2];
  TCoeff add = (shift > 0) ? (1<<(shift-1)) : 0;

  for (j=0; j<line; j++)
  {
    /* Utilizing symmetry properties to the maximum to minimize the number of multiplications */
    for (k=0;k<16;k++)
    {
      O[k] = g_aiT32[TRANSFORM_INVERSE][ 1][k]*src[ line    ] + g_aiT32[TRANSFORM_INVERSE][ 3][k]*src[ 3*line  ] +
             g_aiT32[TRANSFORM_INVERSE][ 5][k]*src[ 5*line  ] + g_aiT32[TRANSFORM_INVERSE][ 7][k]*src[ 7*line  ] +
             g_aiT32[TRANSFORM_INVERSE][ 9][k]*src[ 9*line  ] + g_aiT32[TRANSFORM_INVERSE][11][k]*src[ 11*line ] +
             g_aiT32[TRANSFORM_INVERSE][13][k]*src[ 13*line ] + g_aiT32[TRANSFORM_INVERSE][15][k]*src[ 15*line ] +
             g_aiT32[TRANSFORM_INVERSE][17][k]*src[ 17*line ] + g_aiT32[TRANSFORM_INVERSE][19][k]*src[ 19*line ] +
             g_aiT32[TRANSFORM_INVERSE][21][k]*src[ 21*line ] + g_aiT32[TRANSFORM_INVERSE][23][k]*src[ 23*line ] +
             g_aiT32[TRANSFORM_INVERSE][25][k]*src[ 25*line ] + g_aiT32[TRANSFORM_INVERSE][27][k]*src[ 27*line ] +
             g_aiT32[TRANSFORM_INVERSE][29][k]*src[ 29*line ] + g_aiT32[TRANSFORM_INVERSE][31][k]*src[ 31*line ];
    }
    for (k=0;k<8;k++)
    {
      EO[k] = g_aiT32[TRANSFORM_INVERSE][ 2][k]*src[ 2*line  ] + g_aiT32[TRANSFORM_INVERSE][ 6][k]*src[ 6*line  ] +
              g_aiT32[TRANSFORM_INVERSE][10][k]*src[ 10*line ] + g_aiT32[TRANSFORM_INVERSE][14][k]*src[ 14*line ] +
              g_aiT32[TRANSFORM_INVERSE][18][k]*src[ 18*line ] + g_aiT32[TRANSFORM_INVERSE][22][k]*src[ 22*line ] +
              g_aiT32[TRANSFORM_INVERSE][26][k]*src[ 26*line ] + g_aiT32[TRANSFORM_INVERSE][30][k]*src[ 30*line ];
    }
    for (k=0;k<4;k++)
    {
      EEO[k] = g_aiT32[TRANSFORM_INVERSE][ 4][k]*src[  4*line ] + g_aiT32[TRANSFORM_INVERSE][12][k]*src[ 12*line ] +
               g_aiT32[TRANSFORM_INVERSE][20][k]*src[ 20*line ] + g_aiT32[TRANSFORM_INVERSE][28][k]*src[ 28*line ];
    }
    EEEO[0] = g_aiT32[TRANSFORM_INVERSE][8][0]*src[ 8*line ] + g_aiT32[TRANSFORM_INVERSE][24][0]*src[ 24*line ];
    EEEO[1] = g_aiT32[TRANSFORM_INVERSE][8][1]*src[ 8*line ] + g_aiT32[TRANSFORM_INVERSE][24][1]*src[ 24*line ];
    EEEE[0] = g_aiT32[TRANSFORM_INVERSE][0][0]*src[ 0      ] + g_aiT32[TRANSFORM_INVERSE][16][0]*src[ 16*line ];
    EEEE[1] = g_aiT32[TRANSFORM_INVERSE][0][1]*src[ 0      ] + g_aiT32[TRANSFORM_INVERSE][16][1]*src[ 16*line ];

    /* Combining even and odd terms at each hierarchy levels to calculate the final spatial domain vector */
    EEE[0] = EEEE[0] + EEEO[0];
    EEE[3] = EEEE[0] - EEEO[0];
    EEE[1] = EEEE[1] + EEEO[1];
    EEE[2] = EEEE[1] - EEEO[1];
    for (k=0;k<4;k++)
    {
      EE[k] = EEE[k] + EEO[k];
      EE[k+4] = EEE[3-k] - EEO[3-k];
    }
    for (k=0;k<8;k++)
    {
      E[k] = EE[k] + EO[k];
      E[k+8] = EE[7-k] - EO[7-k];
    }
    for (k=0;k<16;k++)
    {
      dst[k]    = Clip3( outputMinimum, outputMaximum, (E[k] + O[k] + add)>>shift );
      dst[k+16] = Clip3( outputMinimum, outputMaximum, (E[15-k] - O[15-k] + add)>>shift );
    }
    src ++;
    dst += 32;
  }
}



 Void xTrMxN(Int bitDepth, TCoeff *block, TCoeff *coeff, Int iWidth, Int iHeight, Bool useDST, const Int maxLog2TrDynamicRange)
 {
   const Int TRANSFORM_MATRIX_SHIFT = g_transformMatrixShift[TRANSFORM_FORWARD];

   const Int shift_1st = ((g_aucConvertToBit[iWidth] + 2) +  bitDepth + TRANSFORM_MATRIX_SHIFT) - maxLog2TrDynamicRange;
   const Int shift_2nd = (g_aucConvertToBit[iHeight] + 2) + TRANSFORM_MATRIX_SHIFT;

   assert(shift_1st >= 0);
   assert(shift_2nd >= 0);

   TCoeff tmp[ MAX_TU_SIZE * MAX_TU_SIZE ];

   switch (iWidth)
   {
     case 4:
       {
         if ((iHeight == 4) && useDST)    // Check for DCT or DST
         {
            fastForwardDst( block, tmp, shift_1st );
         }
         else
         {
           partialButterfly4 ( block, tmp, shift_1st, iHeight );
         }
       }
       break;

     case 8:     partialButterfly8 ( block, tmp, shift_1st, iHeight );  break;
     case 16:    partialButterfly16( block, tmp, shift_1st, iHeight );  break;
     case 32:    partialButterfly32( block, tmp, shift_1st, iHeight );  break;
     default:
       assert(0); exit (1); break;
   }

   switch (iHeight)
   {
     case 4:
       {
         if ((iWidth == 4) && useDST)    // Check for DCT or DST
         {
           fastForwardDst( tmp, coeff, shift_2nd );
         }
         else
         {
           partialButterfly4 ( tmp, coeff, shift_2nd, iWidth );
         }
       }
       break;

     case 8:     partialButterfly8 ( tmp, coeff, shift_2nd, iWidth );    break;
     case 16:    partialButterfly16( tmp, coeff, shift_2nd, iWidth );    break;
     case 32:    partialButterfly32( tmp, coeff, shift_2nd, iWidth );    break;
     default:
       assert(0); exit (1); break;
   }
 }

/** MxN inverse transform (2D)
*  \param bitDepth              [in]  bit depth
*  \param coeff                 [in]  transform coefficients
*  \param block                 [out] residual block
*  \param iWidth                [in]  width of transform
*  \param iHeight               [in]  height of transform
*  \param useDST                [in]
*  \param maxLog2TrDynamicRange [in]
*/
Void xITrMxN(Int bitDepth, TCoeff *coeff, TCoeff *block, Int iWidth, Int iHeight, Bool useDST, const Int maxLog2TrDynamicRange)
{
  const Int TRANSFORM_MATRIX_SHIFT = g_transformMatrixShift[TRANSFORM_INVERSE];

  Int shift_1st = TRANSFORM_MATRIX_SHIFT + 1; //1 has been added to shift_1st at the expense of shift_2nd
  Int shift_2nd = (TRANSFORM_MATRIX_SHIFT + maxLog2TrDynamicRange - 1) - bitDepth;
  const TCoeff clipMinimum = -(1 << maxLog2TrDynamicRange);
  const TCoeff clipMaximum =  (1 << maxLog2TrDynamicRange) - 1;

  assert(shift_1st >= 0);
  assert(shift_2nd >= 0);

  TCoeff tmp[MAX_TU_SIZE * MAX_TU_SIZE];

  switch (iHeight)
  {
    case 4:
      {
        if ((iWidth == 4) && useDST)    // Check for DCT or DST
        {
          fastInverseDst( coeff, tmp, shift_1st, clipMinimum, clipMaximum);
        }
        else
        {
          partialButterflyInverse4 ( coeff, tmp, shift_1st, iWidth, clipMinimum, clipMaximum);
        }
      }
      break;

    case  8: partialButterflyInverse8 ( coeff, tmp, shift_1st, iWidth, clipMinimum, clipMaximum); break;
    case 16: partialButterflyInverse16( coeff, tmp, shift_1st, iWidth, clipMinimum, clipMaximum); break;
    case 32: partialButterflyInverse32( coeff, tmp, shift_1st, iWidth, clipMinimum, clipMaximum); break;

    default:
      assert(0); exit (1); break;
  }

  switch (iWidth)
  {
    // Clipping here is not in the standard, but is used to protect the "Pel" data type into which the inverse-transformed samples will be copied
    case 4:
      {
        if ((iHeight == 4) && useDST)    // Check for DCT or DST
        {
          fastInverseDst( tmp, block, shift_2nd, std::numeric_limits<Pel>::min(), std::numeric_limits<Pel>::max() );
        }
        else
        {
          partialButterflyInverse4 ( tmp, block, shift_2nd, iHeight, std::numeric_limits<Pel>::min(), std::numeric_limits<Pel>::max());
        }
      }
      break;

    case  8: partialButterflyInverse8 ( tmp, block, shift_2nd, iHeight, std::numeric_limits<Pel>::min(), std::numeric_limits<Pel>::max()); break;
    case 16: partialButterflyInverse16( tmp, block, shift_2nd, iHeight, std::numeric_limits<Pel>::min(), std::numeric_limits<Pel>::max()); break;
    case 32: partialButterflyInverse32( tmp, block, shift_2nd, iHeight, std::numeric_limits<Pel>::min(), std::numeric_limits<Pel>::max()); break;

    default:
      assert(0); exit (1); break;
  }
}
}