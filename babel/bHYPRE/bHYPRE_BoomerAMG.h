/*
 * File:          bHYPRE_BoomerAMG.h
 * Symbol:        bHYPRE.BoomerAMG-v1.0.0
 * Symbol Type:   class
 * Babel Version: 0.9.8
 * sidl Created:  20050317 11:17:39 PST
 * Generated:     20050317 11:17:42 PST
 * Description:   Client-side glue code for bHYPRE.BoomerAMG
 * 
 * WARNING: Automatically generated; changes will be lost
 * 
 * babel-version = 0.9.8
 * source-line   = 1229
 * source-url    = file:/home/painter/linear_solvers/babel/Interfaces.idl
 */

#ifndef included_bHYPRE_BoomerAMG_h
#define included_bHYPRE_BoomerAMG_h

/**
 * Symbol "bHYPRE.BoomerAMG" (version 1.0.0)
 * 
 * Algebraic multigrid solver, based on classical Ruge-Stueben.
 * 
 * The following optional parameters are available and may be set
 * using the appropriate {\tt Parameter} function (as indicated in
 * parentheses):
 * 
 * \begin{description}
 * 
 * \item[MaxLevels] ({\tt Int}) - maximum number of multigrid
 * levels.
 * 
 * \item[StrongThreshold] ({\tt Double}) - AMG strength threshold.
 * 
 * \item[MaxRowSum] ({\tt Double}) -
 * 
 * \item[CoarsenType] ({\tt Int}) - type of parallel coarsening
 * algorithm used.
 * 
 * \item[MeasureType] ({\tt Int}) - type of measure used; local or
 * global.
 * 
 * \item[CycleType] ({\tt Int}) - type of cycle used; a V-cycle
 * (default) or a W-cycle.
 * 
 * \item[NumGridSweeps] ({\tt IntArray 1D}) - number of sweeps for
 * fine and coarse grid, up and down cycle.
 * 
 * \item[GridRelaxType] ({\tt IntArray 1D}) - type of smoother used on
 * fine and coarse grid, up and down cycle.
 * 
 * \item[GridRelaxPoints] ({\tt IntArray 2D}) - point ordering used in
 * relaxation.
 * 
 * \item[RelaxWeight] ({\tt DoubleArray 1D}) - relaxation weight for
 * smoothed Jacobi and hybrid SOR.
 * 
 * \item[TruncFactor] ({\tt Double}) - truncation factor for
 * interpolation.
 * 
 * \item[SmoothType] ({\tt Int}) - more complex smoothers.
 * 
 * \item[SmoothNumLevels] ({\tt Int}) - number of levels for more
 * complex smoothers.
 * 
 * \item[SmoothNumSweeps] ({\tt Int}) - number of sweeps for more
 * complex smoothers.
 * 
 * \item[PrintFileName] ({\tt String}) - name of file printed to in
 * association with {\tt SetPrintLevel}.  (not yet implemented).
 * 
 * \item[NumFunctions] ({\tt Int}) - size of the system of PDEs
 * (when using the systems version).
 * 
 * \item[DOFFunc] ({\tt IntArray 1D}) - mapping that assigns the
 * function to each variable (when using the systems version).
 * 
 * \item[Variant] ({\tt Int}) - variant of Schwarz used.
 * 
 * \item[Overlap] ({\tt Int}) - overlap for Schwarz.
 * 
 * \item[DomainType] ({\tt Int}) - type of domain used for Schwarz.
 * 
 * \item[SchwarzRlxWeight] ({\tt Double}) - the smoothing parameter
 * for additive Schwarz.
 * 
 * \item[DebugFlag] ({\tt Int}) -
 * 
 * \end{description}
 * 
 * Objects of this type can be cast to Solver objects using the
 * {\tt \_\_cast} methods.
 * 
 */
struct bHYPRE_BoomerAMG__object;
struct bHYPRE_BoomerAMG__array;
typedef struct bHYPRE_BoomerAMG__object* bHYPRE_BoomerAMG;

/*
 * Includes for all header dependencies.
 */

#ifndef included_sidl_header_h
#include "sidl_header.h"
#endif
#ifndef included_bHYPRE_Operator_h
#include "bHYPRE_Operator.h"
#endif
#ifndef included_bHYPRE_Vector_h
#include "bHYPRE_Vector.h"
#endif
#ifndef included_sidl_BaseInterface_h
#include "sidl_BaseInterface.h"
#endif
#ifndef included_sidl_ClassInfo_h
#include "sidl_ClassInfo.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Constructor function for the class.
 */
bHYPRE_BoomerAMG
bHYPRE_BoomerAMG__create(void);

void
bHYPRE_BoomerAMG_addRef(
  /*in*/ bHYPRE_BoomerAMG self);

void
bHYPRE_BoomerAMG_deleteRef(
  /*in*/ bHYPRE_BoomerAMG self);

sidl_bool
bHYPRE_BoomerAMG_isSame(
  /*in*/ bHYPRE_BoomerAMG self,
  /*in*/ sidl_BaseInterface iobj);

sidl_BaseInterface
bHYPRE_BoomerAMG_queryInt(
  /*in*/ bHYPRE_BoomerAMG self,
  /*in*/ const char* name);

sidl_bool
bHYPRE_BoomerAMG_isType(
  /*in*/ bHYPRE_BoomerAMG self,
  /*in*/ const char* name);

sidl_ClassInfo
bHYPRE_BoomerAMG_getClassInfo(
  /*in*/ bHYPRE_BoomerAMG self);

/**
 * Set the MPI Communicator.
 * 
 */
int32_t
bHYPRE_BoomerAMG_SetCommunicator(
  /*in*/ bHYPRE_BoomerAMG self,
  /*in*/ void* mpi_comm);

/**
 * Set the int parameter associated with {\tt name}.
 * 
 */
int32_t
bHYPRE_BoomerAMG_SetIntParameter(
  /*in*/ bHYPRE_BoomerAMG self,
  /*in*/ const char* name,
  /*in*/ int32_t value);

/**
 * Set the double parameter associated with {\tt name}.
 * 
 */
int32_t
bHYPRE_BoomerAMG_SetDoubleParameter(
  /*in*/ bHYPRE_BoomerAMG self,
  /*in*/ const char* name,
  /*in*/ double value);

/**
 * Set the string parameter associated with {\tt name}.
 * 
 */
int32_t
bHYPRE_BoomerAMG_SetStringParameter(
  /*in*/ bHYPRE_BoomerAMG self,
  /*in*/ const char* name,
  /*in*/ const char* value);

/**
 * Set the int 1-D array parameter associated with {\tt name}.
 * 
 */
int32_t
bHYPRE_BoomerAMG_SetIntArray1Parameter(
  /*in*/ bHYPRE_BoomerAMG self,
  /*in*/ const char* name,
  /*in*/ struct sidl_int__array* value);

/**
 * Set the int 2-D array parameter associated with {\tt name}.
 * 
 */
int32_t
bHYPRE_BoomerAMG_SetIntArray2Parameter(
  /*in*/ bHYPRE_BoomerAMG self,
  /*in*/ const char* name,
  /*in*/ struct sidl_int__array* value);

/**
 * Set the double 1-D array parameter associated with {\tt name}.
 * 
 */
int32_t
bHYPRE_BoomerAMG_SetDoubleArray1Parameter(
  /*in*/ bHYPRE_BoomerAMG self,
  /*in*/ const char* name,
  /*in*/ struct sidl_double__array* value);

/**
 * Set the double 2-D array parameter associated with {\tt name}.
 * 
 */
int32_t
bHYPRE_BoomerAMG_SetDoubleArray2Parameter(
  /*in*/ bHYPRE_BoomerAMG self,
  /*in*/ const char* name,
  /*in*/ struct sidl_double__array* value);

/**
 * Set the int parameter associated with {\tt name}.
 * 
 */
int32_t
bHYPRE_BoomerAMG_GetIntValue(
  /*in*/ bHYPRE_BoomerAMG self,
  /*in*/ const char* name,
  /*out*/ int32_t* value);

/**
 * Get the double parameter associated with {\tt name}.
 * 
 */
int32_t
bHYPRE_BoomerAMG_GetDoubleValue(
  /*in*/ bHYPRE_BoomerAMG self,
  /*in*/ const char* name,
  /*out*/ double* value);

/**
 * (Optional) Do any preprocessing that may be necessary in
 * order to execute {\tt Apply}.
 * 
 */
int32_t
bHYPRE_BoomerAMG_Setup(
  /*in*/ bHYPRE_BoomerAMG self,
  /*in*/ bHYPRE_Vector b,
  /*in*/ bHYPRE_Vector x);

/**
 * Apply the operator to {\tt b}, returning {\tt x}.
 * 
 */
int32_t
bHYPRE_BoomerAMG_Apply(
  /*in*/ bHYPRE_BoomerAMG self,
  /*in*/ bHYPRE_Vector b,
  /*inout*/ bHYPRE_Vector* x);

/**
 * Set the operator for the linear system being solved.
 * 
 */
int32_t
bHYPRE_BoomerAMG_SetOperator(
  /*in*/ bHYPRE_BoomerAMG self,
  /*in*/ bHYPRE_Operator A);

/**
 * (Optional) Set the convergence tolerance.
 * 
 */
int32_t
bHYPRE_BoomerAMG_SetTolerance(
  /*in*/ bHYPRE_BoomerAMG self,
  /*in*/ double tolerance);

/**
 * (Optional) Set maximum number of iterations.
 * 
 */
int32_t
bHYPRE_BoomerAMG_SetMaxIterations(
  /*in*/ bHYPRE_BoomerAMG self,
  /*in*/ int32_t max_iterations);

/**
 * (Optional) Set the {\it logging level}, specifying the degree
 * of additional informational data to be accumulated.  Does
 * nothing by default (level = 0).  Other levels (if any) are
 * implementation-specific.  Must be called before {\tt Setup}
 * and {\tt Apply}.
 * 
 */
int32_t
bHYPRE_BoomerAMG_SetLogging(
  /*in*/ bHYPRE_BoomerAMG self,
  /*in*/ int32_t level);

/**
 * (Optional) Set the {\it print level}, specifying the degree
 * of informational data to be printed either to the screen or
 * to a file.  Does nothing by default (level=0).  Other levels
 * (if any) are implementation-specific.  Must be called before
 * {\tt Setup} and {\tt Apply}.
 * 
 */
int32_t
bHYPRE_BoomerAMG_SetPrintLevel(
  /*in*/ bHYPRE_BoomerAMG self,
  /*in*/ int32_t level);

/**
 * (Optional) Return the number of iterations taken.
 * 
 */
int32_t
bHYPRE_BoomerAMG_GetNumIterations(
  /*in*/ bHYPRE_BoomerAMG self,
  /*out*/ int32_t* num_iterations);

/**
 * (Optional) Return the norm of the relative residual.
 * 
 */
int32_t
bHYPRE_BoomerAMG_GetRelResidualNorm(
  /*in*/ bHYPRE_BoomerAMG self,
  /*out*/ double* norm);

/**
 * Cast method for interface and class type conversions.
 */
bHYPRE_BoomerAMG
bHYPRE_BoomerAMG__cast(
  void* obj);

/**
 * String cast method for interface and class type conversions.
 */
void*
bHYPRE_BoomerAMG__cast2(
  void* obj,
  const char* type);

struct bHYPRE_BoomerAMG__array*
bHYPRE_BoomerAMG__array_createCol(
  int32_t       dimen,
  const int32_t lower[],
  const int32_t upper[]);

struct bHYPRE_BoomerAMG__array*
bHYPRE_BoomerAMG__array_createRow(
  int32_t       dimen,
  const int32_t lower[],
  const int32_t upper[]);

struct bHYPRE_BoomerAMG__array*
bHYPRE_BoomerAMG__array_create1d(int32_t len);

struct bHYPRE_BoomerAMG__array*
bHYPRE_BoomerAMG__array_create1dInit(
  int32_t len, 
  bHYPRE_BoomerAMG* data);

struct bHYPRE_BoomerAMG__array*
bHYPRE_BoomerAMG__array_create2dCol(int32_t m, int32_t n);

struct bHYPRE_BoomerAMG__array*
bHYPRE_BoomerAMG__array_create2dRow(int32_t m, int32_t n);

struct bHYPRE_BoomerAMG__array*
bHYPRE_BoomerAMG__array_borrow(
  bHYPRE_BoomerAMG* firstElement,
  int32_t       dimen,
  const int32_t lower[],
  const int32_t upper[],
  const int32_t stride[]);

struct bHYPRE_BoomerAMG__array*
bHYPRE_BoomerAMG__array_smartCopy(
  struct bHYPRE_BoomerAMG__array *array);

void
bHYPRE_BoomerAMG__array_addRef(
  struct bHYPRE_BoomerAMG__array* array);

void
bHYPRE_BoomerAMG__array_deleteRef(
  struct bHYPRE_BoomerAMG__array* array);

bHYPRE_BoomerAMG
bHYPRE_BoomerAMG__array_get1(
  const struct bHYPRE_BoomerAMG__array* array,
  const int32_t i1);

bHYPRE_BoomerAMG
bHYPRE_BoomerAMG__array_get2(
  const struct bHYPRE_BoomerAMG__array* array,
  const int32_t i1,
  const int32_t i2);

bHYPRE_BoomerAMG
bHYPRE_BoomerAMG__array_get3(
  const struct bHYPRE_BoomerAMG__array* array,
  const int32_t i1,
  const int32_t i2,
  const int32_t i3);

bHYPRE_BoomerAMG
bHYPRE_BoomerAMG__array_get4(
  const struct bHYPRE_BoomerAMG__array* array,
  const int32_t i1,
  const int32_t i2,
  const int32_t i3,
  const int32_t i4);

bHYPRE_BoomerAMG
bHYPRE_BoomerAMG__array_get5(
  const struct bHYPRE_BoomerAMG__array* array,
  const int32_t i1,
  const int32_t i2,
  const int32_t i3,
  const int32_t i4,
  const int32_t i5);

bHYPRE_BoomerAMG
bHYPRE_BoomerAMG__array_get6(
  const struct bHYPRE_BoomerAMG__array* array,
  const int32_t i1,
  const int32_t i2,
  const int32_t i3,
  const int32_t i4,
  const int32_t i5,
  const int32_t i6);

bHYPRE_BoomerAMG
bHYPRE_BoomerAMG__array_get7(
  const struct bHYPRE_BoomerAMG__array* array,
  const int32_t i1,
  const int32_t i2,
  const int32_t i3,
  const int32_t i4,
  const int32_t i5,
  const int32_t i6,
  const int32_t i7);

bHYPRE_BoomerAMG
bHYPRE_BoomerAMG__array_get(
  const struct bHYPRE_BoomerAMG__array* array,
  const int32_t indices[]);

void
bHYPRE_BoomerAMG__array_set1(
  struct bHYPRE_BoomerAMG__array* array,
  const int32_t i1,
  bHYPRE_BoomerAMG const value);

void
bHYPRE_BoomerAMG__array_set2(
  struct bHYPRE_BoomerAMG__array* array,
  const int32_t i1,
  const int32_t i2,
  bHYPRE_BoomerAMG const value);

void
bHYPRE_BoomerAMG__array_set3(
  struct bHYPRE_BoomerAMG__array* array,
  const int32_t i1,
  const int32_t i2,
  const int32_t i3,
  bHYPRE_BoomerAMG const value);

void
bHYPRE_BoomerAMG__array_set4(
  struct bHYPRE_BoomerAMG__array* array,
  const int32_t i1,
  const int32_t i2,
  const int32_t i3,
  const int32_t i4,
  bHYPRE_BoomerAMG const value);

void
bHYPRE_BoomerAMG__array_set5(
  struct bHYPRE_BoomerAMG__array* array,
  const int32_t i1,
  const int32_t i2,
  const int32_t i3,
  const int32_t i4,
  const int32_t i5,
  bHYPRE_BoomerAMG const value);

void
bHYPRE_BoomerAMG__array_set6(
  struct bHYPRE_BoomerAMG__array* array,
  const int32_t i1,
  const int32_t i2,
  const int32_t i3,
  const int32_t i4,
  const int32_t i5,
  const int32_t i6,
  bHYPRE_BoomerAMG const value);

void
bHYPRE_BoomerAMG__array_set7(
  struct bHYPRE_BoomerAMG__array* array,
  const int32_t i1,
  const int32_t i2,
  const int32_t i3,
  const int32_t i4,
  const int32_t i5,
  const int32_t i6,
  const int32_t i7,
  bHYPRE_BoomerAMG const value);

void
bHYPRE_BoomerAMG__array_set(
  struct bHYPRE_BoomerAMG__array* array,
  const int32_t indices[],
  bHYPRE_BoomerAMG const value);

int32_t
bHYPRE_BoomerAMG__array_dimen(
  const struct bHYPRE_BoomerAMG__array* array);

int32_t
bHYPRE_BoomerAMG__array_lower(
  const struct bHYPRE_BoomerAMG__array* array,
  const int32_t ind);

int32_t
bHYPRE_BoomerAMG__array_upper(
  const struct bHYPRE_BoomerAMG__array* array,
  const int32_t ind);

int32_t
bHYPRE_BoomerAMG__array_length(
  const struct bHYPRE_BoomerAMG__array* array,
  const int32_t ind);

int32_t
bHYPRE_BoomerAMG__array_stride(
  const struct bHYPRE_BoomerAMG__array* array,
  const int32_t ind);

int
bHYPRE_BoomerAMG__array_isColumnOrder(
  const struct bHYPRE_BoomerAMG__array* array);

int
bHYPRE_BoomerAMG__array_isRowOrder(
  const struct bHYPRE_BoomerAMG__array* array);

struct bHYPRE_BoomerAMG__array*
bHYPRE_BoomerAMG__array_slice(
  struct bHYPRE_BoomerAMG__array* src,
  int32_t        dimen,
  const int32_t  numElem[],
  const int32_t  *srcStart,
  const int32_t  *srcStride,
  const int32_t  *newStart);

void
bHYPRE_BoomerAMG__array_copy(
  const struct bHYPRE_BoomerAMG__array* src,
  struct bHYPRE_BoomerAMG__array* dest);

struct bHYPRE_BoomerAMG__array*
bHYPRE_BoomerAMG__array_ensure(
  struct bHYPRE_BoomerAMG__array* src,
  int32_t dimen,
  int     ordering);

#ifdef __cplusplus
}
#endif
#endif
