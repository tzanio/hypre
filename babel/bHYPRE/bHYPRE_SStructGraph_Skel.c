/*
 * File:          bHYPRE_SStructGraph_Skel.c
 * Symbol:        bHYPRE.SStructGraph-v1.0.0
 * Symbol Type:   class
 * Babel Version: 0.9.8
 * sidl Created:  20050317 11:17:39 PST
 * Generated:     20050317 11:17:43 PST
 * Description:   Server-side glue code for bHYPRE.SStructGraph
 * 
 * WARNING: Automatically generated; changes will be lost
 * 
 * babel-version = 0.9.8
 * source-line   = 1027
 * source-url    = file:/home/painter/linear_solvers/babel/Interfaces.idl
 */

#include "bHYPRE_SStructGraph_IOR.h"
#include "bHYPRE_SStructGraph.h"
#include <stddef.h>

extern void
impl_bHYPRE_SStructGraph__ctor(
  bHYPRE_SStructGraph);

extern void
impl_bHYPRE_SStructGraph__dtor(
  bHYPRE_SStructGraph);

extern int32_t
impl_bHYPRE_SStructGraph_SetGrid(
  bHYPRE_SStructGraph,
  bHYPRE_SStructGrid);

extern int32_t
impl_bHYPRE_SStructGraph_SetStencil(
  bHYPRE_SStructGraph,
  int32_t,
  int32_t,
  bHYPRE_SStructStencil);

extern int32_t
impl_bHYPRE_SStructGraph_AddEntries(
  bHYPRE_SStructGraph,
  int32_t,
  struct sidl_int__array*,
  int32_t,
  int32_t,
  struct sidl_int__array*,
  int32_t);

static int32_t
skel_bHYPRE_SStructGraph_AddEntries(
  /*in*/ bHYPRE_SStructGraph self,
  /*in*/ int32_t part,
  /*in*/ struct sidl_int__array* index,
  /*in*/ int32_t var,
  /*in*/ int32_t to_part,
  /*in*/ struct sidl_int__array* to_index,
  /*in*/ int32_t to_var)
{
  int32_t _return;
  struct sidl_int__array* index_proxy = sidl_int__array_ensure(index, 1,
    sidl_column_major_order);
  struct sidl_int__array* to_index_proxy = sidl_int__array_ensure(to_index, 1,
    sidl_column_major_order);
  _return =
    impl_bHYPRE_SStructGraph_AddEntries(
      self,
      part,
      index_proxy,
      var,
      to_part,
      to_index_proxy,
      to_var);
  sidl_int__array_deleteRef(index_proxy);
  sidl_int__array_deleteRef(to_index_proxy);
  return _return;
}

#ifdef __cplusplus
extern "C" {
#endif

void
bHYPRE_SStructGraph__set_epv(struct bHYPRE_SStructGraph__epv *epv)
{
  epv->f__ctor = impl_bHYPRE_SStructGraph__ctor;
  epv->f__dtor = impl_bHYPRE_SStructGraph__dtor;
  epv->f_SetGrid = impl_bHYPRE_SStructGraph_SetGrid;
  epv->f_SetStencil = impl_bHYPRE_SStructGraph_SetStencil;
  epv->f_AddEntries = skel_bHYPRE_SStructGraph_AddEntries;
}
#ifdef __cplusplus
}
#endif

struct bHYPRE_SStructGraph__data*
bHYPRE_SStructGraph__get_data(bHYPRE_SStructGraph self)
{
  return (struct bHYPRE_SStructGraph__data*)(self ? self->d_data : NULL);
}

void bHYPRE_SStructGraph__set_data(
  bHYPRE_SStructGraph self,
  struct bHYPRE_SStructGraph__data* data)
{
  if (self) {
    self->d_data = data;
  }
}
