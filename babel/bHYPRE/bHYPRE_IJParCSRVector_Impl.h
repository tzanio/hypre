/*
 * File:          bHYPRE_IJParCSRVector_Impl.h
 * Symbol:        bHYPRE.IJParCSRVector-v1.0.0
 * Symbol Type:   class
 * Babel Version: 0.9.8
 * sidl Created:  20050317 11:17:39 PST
 * Generated:     20050317 11:17:43 PST
 * Description:   Server-side implementation for bHYPRE.IJParCSRVector
 * 
 * WARNING: Automatically generated; only changes within splicers preserved
 * 
 * babel-version = 0.9.8
 * source-line   = 820
 * source-url    = file:/home/painter/linear_solvers/babel/Interfaces.idl
 */

#ifndef included_bHYPRE_IJParCSRVector_Impl_h
#define included_bHYPRE_IJParCSRVector_Impl_h

#ifndef included_sidl_header_h
#include "sidl_header.h"
#endif
#ifndef included_bHYPRE_IJParCSRVector_h
#include "bHYPRE_IJParCSRVector.h"
#endif
#ifndef included_sidl_BaseInterface_h
#include "sidl_BaseInterface.h"
#endif
#ifndef included_bHYPRE_Vector_h
#include "bHYPRE_Vector.h"
#endif

/* DO-NOT-DELETE splicer.begin(bHYPRE.IJParCSRVector._includes) */
/* Put additional include files here... */
#include "HYPRE_IJ_mv.h"
#include "HYPRE.h"
#include "utilities.h"
/* DO-NOT-DELETE splicer.end(bHYPRE.IJParCSRVector._includes) */

/*
 * Private data for class bHYPRE.IJParCSRVector
 */

struct bHYPRE_IJParCSRVector__data {
  /* DO-NOT-DELETE splicer.begin(bHYPRE.IJParCSRVector._data) */
  /* Put private data members here... */
  HYPRE_IJVector ij_b;
  MPI_Comm comm;
  /* DO-NOT-DELETE splicer.end(bHYPRE.IJParCSRVector._data) */
};

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Access functions for class private data and built-in methods
 */

extern struct bHYPRE_IJParCSRVector__data*
bHYPRE_IJParCSRVector__get_data(
  bHYPRE_IJParCSRVector);

extern void
bHYPRE_IJParCSRVector__set_data(
  bHYPRE_IJParCSRVector,
  struct bHYPRE_IJParCSRVector__data*);

extern void
impl_bHYPRE_IJParCSRVector__ctor(
  bHYPRE_IJParCSRVector);

extern void
impl_bHYPRE_IJParCSRVector__dtor(
  bHYPRE_IJParCSRVector);

/*
 * User-defined object methods
 */

extern int32_t
impl_bHYPRE_IJParCSRVector_Clear(
  bHYPRE_IJParCSRVector);

extern int32_t
impl_bHYPRE_IJParCSRVector_Copy(
  bHYPRE_IJParCSRVector,
  bHYPRE_Vector);

extern int32_t
impl_bHYPRE_IJParCSRVector_Clone(
  bHYPRE_IJParCSRVector,
  bHYPRE_Vector*);

extern int32_t
impl_bHYPRE_IJParCSRVector_Scale(
  bHYPRE_IJParCSRVector,
  double);

extern int32_t
impl_bHYPRE_IJParCSRVector_Dot(
  bHYPRE_IJParCSRVector,
  bHYPRE_Vector,
  double*);

extern int32_t
impl_bHYPRE_IJParCSRVector_Axpy(
  bHYPRE_IJParCSRVector,
  double,
  bHYPRE_Vector);

extern int32_t
impl_bHYPRE_IJParCSRVector_SetCommunicator(
  bHYPRE_IJParCSRVector,
  void*);

extern int32_t
impl_bHYPRE_IJParCSRVector_Initialize(
  bHYPRE_IJParCSRVector);

extern int32_t
impl_bHYPRE_IJParCSRVector_Assemble(
  bHYPRE_IJParCSRVector);

extern int32_t
impl_bHYPRE_IJParCSRVector_GetObject(
  bHYPRE_IJParCSRVector,
  sidl_BaseInterface*);

extern int32_t
impl_bHYPRE_IJParCSRVector_SetLocalRange(
  bHYPRE_IJParCSRVector,
  int32_t,
  int32_t);

extern int32_t
impl_bHYPRE_IJParCSRVector_SetValues(
  bHYPRE_IJParCSRVector,
  int32_t,
  struct sidl_int__array*,
  struct sidl_double__array*);

extern int32_t
impl_bHYPRE_IJParCSRVector_AddToValues(
  bHYPRE_IJParCSRVector,
  int32_t,
  struct sidl_int__array*,
  struct sidl_double__array*);

extern int32_t
impl_bHYPRE_IJParCSRVector_GetLocalRange(
  bHYPRE_IJParCSRVector,
  int32_t*,
  int32_t*);

extern int32_t
impl_bHYPRE_IJParCSRVector_GetValues(
  bHYPRE_IJParCSRVector,
  int32_t,
  struct sidl_int__array*,
  struct sidl_double__array**);

extern int32_t
impl_bHYPRE_IJParCSRVector_Print(
  bHYPRE_IJParCSRVector,
  const char*);

extern int32_t
impl_bHYPRE_IJParCSRVector_Read(
  bHYPRE_IJParCSRVector,
  const char*,
  void*);

#ifdef __cplusplus
}
#endif
#endif
