/* 
 * ip.h
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/*
 * IP.H
 * General include file for Image Processing routines
 * This file also includes headers for libtiff
 * and draw routines
 */

#include "ph.h"
#include "tiffio.h"
#include "draw.h"
#include "lldef.h"
#include "sgl_stat.h"
#include "convolve.h"
#include "pcc2.h"
#include "bdy_stru.h"
#include "misc.h"

/* global constants */
#if defined(WIN32)
#define PI        3.14159265358979
#endif

/* function prototypes */

/* in pv.c */
extern double angular_bend (float *d_phik, float *phi_k, long nv);
extern double arc_length (float *d_lk, float *arc_len, long nv);
extern double vert_to_clen (struct spoint *v, float *s, long nv);
extern double curvature_energy (float *d_phik, float *d_lk, long nv);
extern int find_interior_pt (struct spoint *v, int nv,
                             int *xi, int *yi, int *e_out, double tot_phi);
extern unsigned int reconstruct_poly (float *d_phik, float *d_lk, long nv,
                                      struct spoint *v, struct spoint *porg, int e_outk, double tot_phi, Image * imgIO, int value);
/* in ph.c */
extern void fill_bdy_structure (struct Bdy *bdp, struct spoint *v, long nv,
                                double tot_phi);
extern struct spoint *poly_hull (struct Bdy *bdp, struct spoint *v_ap, double av_dirn, int *hull_area, Image * imgIO, int value);
extern struct spoint *poly_hull_tol (struct Bdy *bdp, struct spoint *v_ap, double av_dirn, int *hull_area, float tol, Image * imgIO, int value);
/* in p_app.c */
extern void poly_approx (struct Bdy *bdp, double tol);
extern void err (char *s, int a1, int a2, int a3, double a4, int a5, int a6,
                 int a7, int a8, int a9, int a10, int a11, int a12);
extern void abort1 (char *s, int a1, int a2, int a3, double a4, int a5, int a6,
                    int a7, int a8, int a9, int a10, int a11, int a12);
#if defined(LINUX)
extern int winding_ccw (Sp *** appp, Sp *** bppp);
extern int winding_cw (Sp *** appp, Sp *** bppp);
#else
extern int winding_ccw (const void *appp, const void *bppp);
extern int winding_cw (const void *appp, const void *bppp);
#endif
extern void convex_hull (struct Bdy *bdp);
extern struct spoint *reprt_hull_center (void);

/* in sgl_stat.c */
extern float nematic_op (int n_sgl, int n_segm, float *dirns);
extern float eccentr (struct Segm *segm, struct linklist *list,
                      float *len, float *width);
extern void find_ex_hist (int n_segm, float *asp_ratio,
                          int *ex_hist, double bw, double ar_base);
extern int zero_moment (int nv, int *xv, int *yv);
extern void find_area_hist (int n_segm, int *area,
                            int *area_hist, int bw, int area_base);
extern void find_lsz_hist (int n_segm, int *lsize, int *lsz_hist,
                           int nbins, int lsz_base);

/* in pmom.c */
extern struct spoint *poly_moments (long nv, struct spoint *v, float *moments, Image * imgIO, int value);

#if defined(WIN32)
/* in getopt.c */
static void get_next_index (void);
extern int getopt (int argc, char **argv, char *optstring);
#endif

/* in ip.c */
extern void exitmess (char *prompt, int status);

/* in fft.c */
extern void fft (int npoints, float *real, float *imag, int inv);

/* in fft2d.c */
extern void fft2d (float **imgReal, float **imgImag, register long nRow, register long nCol, short flag);

/* in fltrbttr.c */
extern void fltrbttr (float **imgReal, float **imgImag, long nRow, long nCol, short passType, double f1, double f2, double order);

/* in fltrgaus.c */
extern void fltrgaus (float **imgReal, float **imgImag, long nRow, long nCol, short passType, double f1, double f2);

/* in convolve.c */
extern int convolve (Image * ImageIn, Image * ImageOut, Matrix * Kernel);

/* in n2_pv.c */
extern int vert_to_phi_star (struct spoint *v, long nv, float *phi_star);
extern double zero_mom (struct spoint *v, long nv);
extern double shape_parm (double c_len, float *moments);
extern double E_dist (struct spoint *pt1, struct spoint *pt2);
extern double tg_turn_an (double m1, double m2);
extern double slope (struct spoint *pt1, struct spoint *pt2);
extern double vcp (struct spoint *v1, struct spoint *v2);
extern double cont_bend_en (struct spoint *v, long nv);
extern void r_dev (struct spoint *vc, struct spoint *v, float *r, long nv, float *moments, Image * imgIO, int value);
extern void n2_vert (struct spoint *v, float *s, long nv, struct spoint *v_n2, long nv2, Image * imgIO, int value);

/* proc_poly.c */
extern struct polygon *select_poly (struct polygon *poly_head, Image * imgIO, int value);

/* acm_io.c */
extern int acm_prm_size (FILE * file);
extern int acm_cont_parms (FILE * file);
extern int acm_record_size (FILE * file);
extern int acm_moments (FILE * file);
extern void acm_shape_parms (FILE * file, float *c_len, float *area,
                             float *pc_len, float *p2a, float *e_bend);
extern void get_acm_data (FILE * file,
                          int n_mode_parms, int *mode_parms, int n_moments,
             float *moments, int n_pts, float *power_spec, float *corr_fct);
extern void write_acm_file (FILE * file,
                        long nv2, float *p_spec, float *acf, float *moments,
                         int n_mom, int *mode_parms, int n_mp, double c_len,
            double pix_ct, double res_c_len, double g_shape, double e_bend);
extern void write_fd_file (FILE * file, int n_order, float *a_n,
                           double length, double area, double ratio);

/* descript.c */
extern void descriptors (float *dphik, float *dlk, long mcp,
                         float *a_n, float *b_n, long n_order);
extern void msdescriptors (float *delta_phik, float *delta_lk,
                           long mcp, float *a_n, float *b_n, long n_order);
extern void vdot (float *dphik, float *dlk, float *dc_term, long mcp);
extern void vsin (float *source, float *dest, long mcp);
extern void vcos (float *source, float *dest, long mcp);
extern void vrtop (float *x, float *y, float *mod, float *arg, long mcp);

/* psaf.c */
extern void psaf (long n2, float *inp, float *cf, float *ps);
extern void spec_and_corr (long n2, float *inp, float *cf, float *ps);
extern double spec_bend_en (long nv, float *ps, double c_len);

/* license.c */
extern void print_sos_lic ();
extern void print_bcd_lic ();

#if defined(LINUX)
#define flushall() {fflush(stdin);fflush(stdout);fflush(stderr);}
#endif
