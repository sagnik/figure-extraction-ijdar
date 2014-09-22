/* 
 * bdy_stru.h
 * 
 * Practical Algorithms for Image Analysis
 * 
 * Copyright (c) 1997, 1998, 1999 MLMSoftwareGroup, LLC
 */

/*
 * BDY_STRUC.H
 *
 */

#ifndef _BDYSTRUC_H_
#define	_BDYSTRUC_H_

/*
 * curvature point
 */
struct curv_points {
  int xn, yn, edge_in, edge_out;
  struct curv_points *prev;
  struct curv_points *next;
  struct curv_points *same_point;
};

/*
 * polygon
 */
struct polygon {
  float *d_phi_ptr, *d_l_ptr;
  long poly_points;
  int first_x;
  int first_y;
  int first_edge_out;
  float total_delta_phi;
  struct polygon *next_poly;
  struct polygon *prev_poly;
};

#endif /* _BDYSTRUC_H_ */
