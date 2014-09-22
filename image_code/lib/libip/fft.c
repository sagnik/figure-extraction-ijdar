/* 
 * fft.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

#define PI	3.14159265358979

/*
 * fft()
 *   DESCRIPTION:
 *       Uses time decomposition with input bit reversal. The Cooley/Tookey
 *       Fortran scheme for doing recursive odd/even decimation without really
 *       doing bit reversal is used. The computation is done in place, so the
 *       output replaces the input.  The contents of the arrays are changed
 *     from the input data to the FFT coefficients.
 *   ARGUMENTS:
 *       npoints(int) the number of points in the FFT. Must be a power of 2.
 *       real, imag(float *) pointers to arrays of floats for input and output.
 *       inv(int)       inv = 1 for inverse transform
 *                      inv = -1 for forward transform
 *   RETURN VALUE:
 *     none
 */
void
fft (npoints, real, imag, inv)
     int npoints, inv;
     float *real, *imag;
{
  register int i, index, swapindex, j, k;
  register float tr, ti, angle, wr, wi;
  double sin (), cos ();

  /* SWAP THE INPUT ELEMENTS FOR THE DECIMATION IN TIME ALGORITHM. */
  for (index = 1, swapindex = 0; index < npoints; index++) {
    k = npoints;
    do
      k /= 2;
    while ((swapindex + k) >= npoints);
    swapindex = (swapindex % k) + k;
    if (swapindex <= index)
      continue;
    tr = real[index];
    real[index] = real[swapindex];
    real[swapindex] = tr;
    ti = imag[index];
    imag[index] = imag[swapindex];
    imag[swapindex] = ti;
  }

  /*
   * DO THE BUTTERFLY COMPUTATIONS.
   *      stage index:    k = 1, 2, 4, 8 . . .
   *                      For npoints = 8, for example, there will
   *                      be three stages of butterfly computations.
   *      b'fly indices:  i and j will be separated by a distance
   *                      dependent on the current stage.
   *                      k is used as the separation constant.
   */

  for (k = 1; k < npoints; k *= 2)
    for (index = 0; index < k; index++) {
      angle = (float) PI *((float) index * inv) / ((float) k);
      wr = (float) cos (angle);
      wi = (float) sin (angle);
      for (i = index; i < npoints; i += 2 * k) {
        j = i + k;
        tr = (wr * (real[j])) - (wi * (imag[j]));
        ti = (wr * (imag[j])) + (wi * (real[j]));
        real[j] = real[i] - tr;
        imag[j] = imag[i] - ti;
        real[i] += tr;
        imag[i] += ti;
      }
    }

  /* for inverse transform, scale output by 1/N */
  if (inv == 1)
    for (i = 0; i < npoints; i++) {
      real[i] = real[i] / npoints;
      imag[i] = imag[i] / npoints;
    }
}
