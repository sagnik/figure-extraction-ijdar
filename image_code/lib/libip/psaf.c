/* 
 * acm_io.c
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/*
 * PSAF
 *
 * function to compute power_spectrum and autocorrelation by FFT:
 *   for angular bend function (-->tan mode) 
 *   for radial function (-->rad mode)
 *   for both (-->all);
 *   -->note: normalization is to N2_VERTEX!!
 *
 * evaluate bending energy on basis of spectral densities
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ip.h"


#define log2(a) (log(a)/ 0.6931471805599)
#define exp2(a) (pow((double)2, (double)a))
#define	AP_N_LOC	0

#define	FETCH_ALL	1
#undef CHECK_INPUT


/*
 * psaf()
 *   DESCRIPTION:
 *     evaluate power spectrum and autocorrelation function
 *   ARGUMENTS:
 *     n2: input vector size (long)
 *     inp: input vector (float*)
 *     cf: output vector for correlation function (float*)
 *     ps: output vector for power spectrum (float *)
 *   RETURN VALUE:
 *     none
 */

void
psaf (long n2, float *inp, float *cf, float *ps)
{
  int i;
  long n_pow2;
  double temp;
  float *imagp;
  float *realp;
  float inp_max;

  /*
   * check for input vector size = power of 2
   */
  n_pow2 = n2;
  temp = log2 ((double) n2);
  if ((temp - (long) temp) != 0.0)
    n_pow2 = (long) exp2 ((double) ((long) temp));
  if (n_pow2 != n2) {
    printf ("psaf: Input vector length (n2 = %d) not power of two!! (required for FFT).\nExiting...\n", n2);
    exit (1);
  }

  if ((realp = (float *) calloc (n2, sizeof (float))) == NULL)
      exitmess ("\npasf:...mem allocation for real failed\n", 1);
  if ((imagp = (float *) calloc (n2, sizeof (float))) == NULL)
      exitmess ("\npasf:...mem allocation for imag failed\n", 1);

  inp_max = (float) 0.0;
  /*
   * copy the input array to the real array
   */
  for (i = 0; i < n2; i++) {
    *(realp + i) = *(inp + i);
    if (*(inp + i) > inp_max)
      inp_max = *(inp + i);
  }

  /*
   * normalize
   */
  for (i = 0; i < n2; i++)
    *(realp + i) /= inp_max;

  /*
   * now do the forward 1-D fft
   */
  fft (n2, realp, imagp, -1);

  /*
   * calculate the magnitude of the coefficients
   * to get the power spectrum
   */
  for (i = 0; i < n2; i++)
    *(ps + i) = ((*(realp + i) * *(realp + i)) + (*(imagp + i) * *(imagp + i)));

  /*
   *       -->note: 
   *          strictly speaking, power spectrum should not 
   *          be divided by n2
   */
  printf ("\n...power spectrum (n = %ld):\n", n2);
  for (i = 0; i < n2; i++) {
    //*(ps + i) = *(ps + i)/(float)n2;
    printf ("%7.4f  ", *(ps + i));
    if ((i + 1) % 8 == 0)
      printf ("\n");
  }

  /*
   * if desired, real and imaginary parts of the (complex) FFT may be printed, 
   */
  if (FETCH_ALL == 1) {
    printf ("\n\n...real part of CFFT:\n");
    for (i = 0; i < n2; i++) {
      printf ("%7.4f  ", *(realp + i));
      if ((i + 1) % 8 == 0)
        printf ("\n");
    }

    printf ("\n\n...imaginary part of CFFT:\n");
    for (i = 0; i < n2; i++) {
      printf ("%7.4f  ", *(imagp + i));
      if ((i + 1) % 8 == 0)
        printf ("\n");
    }
  }
  printf ("\n...prepare to compute back transform:");
  /*
   * copy the power spectrum array to the real array
   * and zero the imag array
   */
  for (i = 0; i < n2; i++) {
    *(realp + i) = *(ps + i);
    *(imagp + i) = (float) 0.0;
  }

  /*
   * now do the reverse 1-D fft
   */
  fft (n2, realp, imagp, -1);

  /*
   * copy the real part to the autocorrelation array
   */
  for (i = 0; i < n2; i++)
    *(cf + i) = *(realp + i);

  printf ("\n...output of autocorrelation (n = %ld):\n", n2);
  for (i = 0; i < n2; i++) {
    /*
     * Ordinarily one would multiply by n2, but
     * given our definition of fft(), we don't
     */
    //*(cf+i) *= (float)n2;
    printf ("%7.4f  ", *(cf + i));
    if ((i + 1) % 8 == 0)
      printf ("\n");
  }
  free (realp);
  free (imagp);
  return;
}


/*
 * power spectrum and correlation function
 *
 * 1D discrete autocorrelation function, using FFT
 */

/*
 * spec_and_corr()
 *   DESCRIPTION:
 *     1D discrete autocorrelation function, using FFT
 *     wrapper for psaf
 *   ARGUMENTS:
 *     n2: input vector size (long)
 *     inp: input vector (float*)
 *     cf: output vector for correlation function (float*)
 *     ps: output vector for power spectrum (float *)
 *   RETURN VALUE:
 *     none
 */

void
spec_and_corr (long n2, float *inp, float *cf, float *ps)
{

#ifdef CHECK_INPUT
  int i;

  printf ("\n...AP input data:\n");
  printf ("...n2 = %ld\n", n2);
  for (i = 0; i < n2; i++) {
    printf ("%7.4f  ", *(inp + i));
    if ((i + 1) % 8 == 0)
      printf ("\n");
  }
#endif



/*
 * evaluate power spectrum and autocorrelation function by 1D-FFT
 */
  psaf (n2, inp, cf, ps);

}


/*
 * spec_bend_en()
 *   DESCRIPTION:
 *     evaluate bending energy
 *     ref: Young et al., Information & Control 25, 357-370 (1974)
 *     -- note: 
 *       dependent on parametrization of contour and normalization of
 *       shape function;
 *       strictly defined for radial function only;
 *   ARGUMENTS:
 *     nv: input vector size (long)
 *     ps: input vector for power spectrum (float *)
 *     c_len: curvature length (double)
 *   RETURN VALUE:
 *     bending energy (double)
 */
double
spec_bend_en (nv, ps, c_len)
     long nv;
     float *ps;
     double c_len;
{
  int i, i4;
  double om0, ps2;
  double e_bend;

  e_bend = 0.0;
  for (i = 0; i < nv; i++) {
    i4 = i * i * i * i;
    ps2 = (*(ps + i)) * (*(ps + i));
    e_bend += (i4 * ps2);
  }
  om0 = 2.0 * M_PI / c_len;
  e_bend *= om0 * om0 * om0 * om0;
  printf ("\n...bending energy (from spectrum) = %lf\n", e_bend);

  return (e_bend);
}
