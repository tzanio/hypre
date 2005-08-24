/*
   Example 6

   Interface:      Semi-Structured interface (SStruct)

   Compile with:   make ex6

   Sample run:     mpirun -np 2 ex6

   To see options: ex6 -help

   Description:  This is a two processor example and is the same problem
                 as is solved with the structured interface in Example 2. 
                 (The grid boxes are exactly those in the example
                 diagram in the struct interface chapter of the User's Manual.
                 Processor 0 owns two boxes and processor 1 owns one box.)
                 This is the simplest sstruct example.  There is one part and 
                 one variable. 

                 The solver is PCG with SMG preconditioner. We use a 
                 structured solver for this example.

                  

*/

#include <stdio.h>
#include <stdlib.h>

/* SStruct linear solvers headers */
#include "HYPRE_sstruct_mv.h"
#include "HYPRE_sstruct_ls.h"


int main (int argc, char *argv[])
{

   int myid, num_procs;
   
   HYPRE_SStructGrid     grid;
   HYPRE_SStructGraph    graph;
   HYPRE_SStructStencil  stencil;
   HYPRE_SStructMatrix   A;
   HYPRE_SStructVector   b;
   HYPRE_SStructVector   x;

   /* We are using struct solvers for this example */
   HYPRE_StructSolver   solver;
   HYPRE_StructSolver   precond;

   int object_type;

   /* Initialize MPI */
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &myid);
   MPI_Comm_size(MPI_COMM_WORLD, &num_procs);


   if (num_procs != 2)
   {
      if (myid ==0) printf("Must run with 2 processors!\n");
      MPI_Finalize();
      
      return(0);
   }

   /* 1. Set up the 2D grid.   Here we only use one part and
         one variable. (So the part id is 0 and the variable id is 0)*/
   {
      
      int ndim = 2;
      int nparts = 1;
      int part = 0;
      
    
      /* Create an empty 2D grid object */
      HYPRE_SStructGridCreate(MPI_COMM_WORLD, ndim, nparts, &grid);
            
      /* Set the extents of the grid - each processor sets its grid 
         boxes.  Each part has its own relative index space numbering,
         but in this example all boxes belong to the same part.*/


      /* Processor 0 owns two boxes in the grid. */
      if (myid == 0)
      {
         /* Add a new box to the grid */
         {
            int ilower[2] = {-3, 1};
            int iupper[2] = {-1, 2};

            HYPRE_SStructGridSetExtents(grid, part, ilower, iupper);
         }

         /* Add a new box to the grid */
         {
            int ilower[2] = {0, 1};
            int iupper[2] = {2, 4};

            HYPRE_SStructGridSetExtents(grid, part, ilower, iupper);
         }
      }

      /* Processor 1 owns one boxes in the grid. */
      else if (myid == 1)
      {
         /* Add a new box to the grid */
         {
            int ilower[2] = {3, 1};
            int iupper[2] = {6, 4};

            HYPRE_SStructGridSetExtents(grid, part, ilower, iupper);
         }
      }
   
      /* Set the variable type and number of variables on each part.  Processors do
      these even for parts where they do not own boxes if the part will neighbor
      some of its boxes.  In this example, we only have one part. */
      {
         int nvars = 1;
         int i;
         HYPRE_SStructVariable  vartypes[1] = {HYPRE_SSTRUCT_VARIABLE_CELL};

         for (i = 0; i< nparts; i++)
         {
            HYPRE_SStructGridSetVariables(grid, i, nvars, vartypes);
         }
         
      }
      
      /* Now the grid is ready to use */
      HYPRE_SStructGridAssemble(grid);

   } 


   /* 2. Define the discretization stencil(s) */
   {

      int ndim = 2;
      int stencil_size = 5;
      

      /* Create an empty 2D, 5-pt stencil object */
      HYPRE_SStructStencilCreate(ndim, stencil_size, &stencil);

      /* Define the geometry of the stencil. Each represents a
         relative offset (in the index space). */
      {
         int entry;
         int offsets[5][2] = {{0,0}, {-1,0}, {1,0}, {0,-1}, {0,1}};
         int var = 0;
         
         
         /* Assign numerical values to the offsets so that we can
            easily refer to them  - the last argument indicates the
            variable for which we are assigning this stencil - we are
            just using one variable in this example so it is the first one (0)*/

         for (entry = 0; entry < stencil_size; entry++)
            HYPRE_SStructStencilSetEntry(stencil, entry, offsets[entry], var);
      }
      
   }
   

   /* 3. Set up the Graph  - this determines the non-zero structure
      of the matrix and allows non-stencil relationships between part data.*/
   {
      
      int var = 0;
      int part = 0;
      

      /* Create the graph object */
      HYPRE_SStructGraphCreate(MPI_COMM_WORLD, grid, &graph);
      
      /* Now we need to tell the graph which stencil to use for each
         variable on each part (we only have one variable and one part)*/
 
      HYPRE_SStructGraphSetStencil(graph, part, var, stencil);


      /* Here we could establish connections between parts if we
         had more than one part using the graph. For example, we could
         use HYPRE_GraphAddEntries() routine or HYPRE_GridSetNeighborBox()*/


      /* Assemble the graph */
      HYPRE_SStructGraphAssemble(graph);

   }


   /* 4. Set up a SStruct Matrix */
   {

      int part = 0;
      int var = 0;
      int i,j;
     
      /* Create the empty matrix object */
      HYPRE_SStructMatrixCreate(MPI_COMM_WORLD, graph, &A);
      

      /* Set the object type - the default is HYPRE_SSTRUCT. This
         determines the storage of the matrix (the data structure used). 
         If you want to use unstructured solvers (like BoomerAMG), for example,
         the object type should be HYPRE_PARCSR.  If the problem is purely
         structured (with one part), you may want to use HYPRE_STRUCT to 
         to access the structured solvers. Here we have a purely structured example.  */


      object_type = HYPRE_STRUCT;
      HYPRE_SStructMatrixSetObjectType(A, object_type);
      

      /* Get ready to set values */
      HYPRE_SStructMatrixInitialize(A);

      /* Each processor must set the stencil values for
         their boxes on each part.  In this example, we 
         only set stencil entries and therefore use
         HYPRE_SStructMatrixSetBoxValues.  If we needed to 
         set non-stencil entries, we would use 
         HYPRE_SStructMatrixSetValues (shown in a later example).
      */


      if (myid == 0)
      {
         /* Set the matrix coefficients for some set of stencil entries
            over all the gridpoints in my first box (account for boundary
            grid points later) */
         {
            int ilower[2] = {-3, 1};
            int iupper[2] = {-1, 2};

            int nentries = 5;   /* 5-point stencil */
            int stencil_indices[5];

            int nvalues  = nentries*6; /* 6 grid points  */
            double* values;


            values = calloc(nvalues, sizeof(double));

            for (j = 0; j < nentries; j++) /* label the stencil indices -
                                              these correspond to the offsets
                                              defined above */
               stencil_indices[j] = j;

            for (i = 0; i < nvalues; i += nentries)
            {
               values[i] = 4.0;
               for (j = 1; j < nentries; j++)
                  values[i+j] = -1.0;
            }

            HYPRE_SStructMatrixSetBoxValues(A, part, ilower, iupper, 
                                            var, nentries,
                                            stencil_indices, values);

            free(values);
            
         }

         /* Set the matrix coefficients for some set of stencil entries
            over the gridpoints in my second box */
         {
            int ilower[2] = {0, 1};
            int iupper[2] = {2, 4};

            int nentries = 5;
            int stencil_indices[5];

            int nvalues  = 12*nentries; /* 12 grid points*/
            double *values;

            values = calloc(nvalues, sizeof(double));
           
            for (j = 0; j < nentries; j++)
               stencil_indices[j] = j;

            for (i = 0; i < nvalues; i += nentries)
            {
               values[i] = 4.0;
               for (j = 1; j < nentries; j++)
                  values[i+j] = -1.0;
            }

            HYPRE_SStructMatrixSetBoxValues(A, part, ilower, iupper, 
                                            var, nentries,
                                            stencil_indices, values);
            free(values);

         }
      }
      else if (myid == 1)
      {
         /* Set the matrix coefficients for some set of stencil entries
            over the gridpoints in my box */
         {
            int ilower[2] = {3, 1};
            int iupper[2] = {6, 4};

            int nentries = 5;
            int stencil_indices[5];

            int nvalues  = 16*nentries; /* 16 grid points */
            double *values;

            values = calloc(nvalues, sizeof(double));
        
            for (j = 0; j < nentries; j++)
               stencil_indices[j] = j;

            for (i = 0; i < nvalues; i += nentries)
            {
               values[i] = 4.0;
               for (j = 1; j < nentries; j++)
                  values[i+j] = -1.0;
            }

            HYPRE_SStructMatrixSetBoxValues(A, part, ilower, iupper, 
                                           var, nentries,
                                           stencil_indices, values);

            free(values);
            
         }
      }

      /* For each box, set any coefficients that reach ouside of the
         boundary to 0 */
      if (myid == 0)
      {
         int maxnvalues = 6;
         double values[6];

         for (i = 0; i < maxnvalues; i++)
            values[i] = 0.0;

         {
            /* Values below our first AND second box */
            int ilower[2] = {-3, 1};
            int iupper[2] = { 2, 1};

            int stencil_indices[1] = {3};

            HYPRE_SStructMatrixSetBoxValues(A, part, ilower, iupper, 
                                            var, 1,
                                           stencil_indices, values);
         }

         {
            /* Values to the left of our first box */
            int ilower[2] = {-3, 1};
            int iupper[2] = {-3, 2};

            int stencil_indices[1] = {1};

            HYPRE_SStructMatrixSetBoxValues(A, part, ilower, iupper, 
                                            var, 1,
                                            stencil_indices, values);
         }

         {
            /* Values above our first box */
            int ilower[2] = {-3, 2};
            int iupper[2] = {-1, 2};

            int stencil_indices[1] = {4};

            HYPRE_SStructMatrixSetBoxValues(A, part, ilower, iupper, 
                                           var, 1,
                                           stencil_indices, values);
         }

         {
            /* Values to the left of our second box (that do not border the
               first box). */
            int ilower[2] = { 0, 3};
            int iupper[2] = { 0, 4};

            int stencil_indices[1] = {1};

            HYPRE_SStructMatrixSetBoxValues(A, part, ilower, iupper, 
                                            var, 1,
                                            stencil_indices, values);
         }

         {
            /* Values above our second box */
            int ilower[2] = { 0, 4};
            int iupper[2] = { 2, 4};

            int stencil_indices[1] = {4};

            HYPRE_SStructMatrixSetBoxValues(A, part, ilower, iupper, 
                                           var, 1,
                                           stencil_indices, values);
         }
      }
      else if (myid == 1)
      {
         int maxnvalues = 4;
         double values[4];
         for (i = 0; i < maxnvalues; i++)
            values[i] = 0.0;

         {
            /* Values below our box */
            int ilower[2] = { 3, 1};
            int iupper[2] = { 6, 1};

            int stencil_indices[1] = {3};

            HYPRE_SStructMatrixSetBoxValues(A, part, ilower, iupper, 
                                            var, 1,
                                            stencil_indices, values);
         }

         {
            /* Values to the right of our box */
            int ilower[2] = { 6, 1};
            int iupper[2] = { 6, 4};

            int stencil_indices[1] = {2};

            HYPRE_SStructMatrixSetBoxValues(A, part, ilower, iupper, 
                                           var, 1,
                                           stencil_indices, values);
         }

         {
            /* Values above our box */
            int ilower[2] = { 3, 4};
            int iupper[2] = { 6, 4};

            int stencil_indices[1] = {4};

            HYPRE_SStructMatrixSetBoxValues(A, part, ilower, iupper, 
                                            var, 1,
                                            stencil_indices, values);
         }
      }

      /* This is a collective call finalizing the matrix assembly.
         The matrix is now ``ready to be used'' */
      HYPRE_SStructMatrixAssemble(A);
   }


 /* 5. Set up SStruct Vectors for b and x.  */
   {

      int i;
      

      /* We have one part and one variable. */
      int part = 0;
      int var = 0;
      

      /* Create an empty vector object */
      HYPRE_SStructVectorCreate(MPI_COMM_WORLD, grid, &b);
      HYPRE_SStructVectorCreate(MPI_COMM_WORLD, grid, &x);

           
      /* As with the matrix,  set the object type for the vectors 
         to be the struct type */  
      object_type = HYPRE_STRUCT;
      HYPRE_SStructVectorSetObjectType(b, object_type);
      HYPRE_SStructVectorSetObjectType(x, object_type);


      /* Indicate that the vector coefficients are ready to be set */
      HYPRE_SStructVectorInitialize(b);
      HYPRE_SStructVectorInitialize(x);

      if (myid == 0)
      {
         /* Set the vector coefficients over the gridpoints in my first box */
         {
            int ilower[2] = {-3, 1};
            int iupper[2] = {-1, 2};

            int nvalues = 6;  /* 6 grid points */
            double values[6];

            for (i = 0; i < nvalues; i ++)
               values[i] = 1.0;
            HYPRE_SStructVectorSetBoxValues(b, part, ilower, iupper, var, values);

            for (i = 0; i < nvalues; i ++)
               values[i] = 0.0;
            HYPRE_SStructVectorSetBoxValues(x, part, ilower, iupper, var, values);
         }

         /* Set the vector coefficients over the gridpoints in my second box */
         {
            int ilower[2] = { 0, 1};
            int iupper[2] = { 2, 4};

            int nvalues = 12; /* 12 grid points */
            double values[12];

            for (i = 0; i < nvalues; i ++)
               values[i] = 1.0;
            HYPRE_SStructVectorSetBoxValues(b, part, ilower, iupper, var, values);

            for (i = 0; i < nvalues; i ++)
               values[i] = 0.0;
            HYPRE_SStructVectorSetBoxValues(x, part, ilower, iupper, var, values);
         }
      }
      else if (myid == 1)
      {
         /* Set the vector coefficients over the gridpoints in my box */
         {
            int ilower[2] = { 3, 1};
            int iupper[2] = { 6, 4};

            int nvalues = 16; /* 16 grid points */
            double values[16];

            for (i = 0; i < nvalues; i ++)
               values[i] = 1.0;
            HYPRE_SStructVectorSetBoxValues(b, part, ilower, iupper, var, values);

            for (i = 0; i < nvalues; i ++)
               values[i] = 0.0;
            HYPRE_SStructVectorSetBoxValues(x, part, ilower, iupper, var, values);
         }
      }

      /* This is a collective call finalizing the vector assembly.
         The vectors are now ``ready to be used'' */
      HYPRE_SStructVectorAssemble(b);
      HYPRE_SStructVectorAssemble(x);
   }


   /* 6. Set up and use a solver (See the Reference Manual for descriptions
      of all of the options.) */
   {

      HYPRE_StructMatrix    sA;
      HYPRE_StructVector    sb;
      HYPRE_StructVector    sx;
      
      /* Because we are using a struct solver, we need to get the 
         object of the matrix and vectors to pass in to the struct solvers */  

      HYPRE_SStructMatrixGetObject(A, (void **) &sA);
      HYPRE_SStructVectorGetObject(b, (void **) &sb);
      HYPRE_SStructVectorGetObject(x, (void **) &sx);


      /* Create an empty PCG Struct solver */
      HYPRE_StructPCGCreate(MPI_COMM_WORLD, &solver);

      /* Set some parameters */
      HYPRE_StructPCGSetTol(solver, 1.0e-06);
      HYPRE_StructPCGSetPrintLevel(solver, 2);
      HYPRE_StructPCGSetMaxIter(solver, 50);

      /* Create the Struct SMG solver for use as the 
         preconditioner */
      HYPRE_StructSMGCreate(MPI_COMM_WORLD, &precond);

      /* Set a few parameters */
      HYPRE_StructSMGSetMaxIter(precond, 1);
      HYPRE_StructSMGSetTol(precond, 0.0);
      HYPRE_StructSMGSetZeroGuess(precond);
      HYPRE_StructSMGSetNumPreRelax(precond, 1);
      HYPRE_StructSMGSetNumPostRelax(precond, 1);

      /* Set preconditioner and solve */
      HYPRE_StructPCGSetPrecond(solver, HYPRE_StructSMGSolve,
                           HYPRE_StructSMGSetup, precond);
      HYPRE_StructPCGSetup(solver, sA, sb, sx);
      HYPRE_StructPCGSolve(solver, sA, sb, sx);
      
   }
   
   /* Free memory */
   HYPRE_SStructGridDestroy(grid);
   HYPRE_SStructStencilDestroy(stencil);
   HYPRE_SStructGraphDestroy(graph);
   HYPRE_SStructMatrixDestroy(A);
   HYPRE_SStructVectorDestroy(b);
   HYPRE_SStructVectorDestroy(x);

   HYPRE_StructPCGDestroy(solver);
   HYPRE_StructSMGDestroy(precond);


   /* Finalize MPI */
   MPI_Finalize();

   return (0);
}