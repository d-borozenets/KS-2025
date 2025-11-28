#ifndef MPI_STUB_H
#define MPI_STUB_H

/* --------------------------------------------------------------
   MPI STUB HEADER FOR WINDOWS (EDITOR SUPPORT ONLY)
   This file provides:
     - documentation tooltips for CLion
     - autocomplete for MPI symbols
     - minimal typedefs and constants
     - NO IMPLEMENTATION (not for compilation)
   -------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {

#endif

/* ============================
   BASIC TYPES
   ============================ */

/**
 * @brief MPI communicator handle (stub)
 */
typedef int MPI_Comm;

/**
 * @brief MPI datatype handle (stub)
 */
typedef int MPI_Datatype;

/**
 * @brief MPI request object (stub)
 */
typedef int MPI_Request;

/**
 * @brief Minimal MPI_Status struct (stub)
 */
typedef struct MPI_Status {
    int MPI_SOURCE; /**< Rank of the source process */
    int MPI_TAG; /**< Message tag */
    int MPI_ERROR; /**< Error code */
} MPI_Status;

/* Predefined status ignore pointer */
static MPI_Status _mpi_stub_status_ignore;
#define MPI_STATUS_IGNORE ((MPI_Status*)&_mpi_stub_status_ignore)

/* ============================
   CONSTANTS
   ============================ */

#define MPI_COMM_WORLD   0  /**< Global communicator */
#define MPI_COMM_SELF    1  /**< Self communicator */

/* Datatypes */
#define MPI_INT          0
#define MPI_FLOAT        1
#define MPI_DOUBLE       2
#define MPI_CHAR         3
#define MPI_LONG         4

/* Operations for reductions */
#define MPI_SUM          0
#define MPI_MAX          1
#define MPI_MIN          2

/* Return codes */
#define MPI_SUCCESS      0

/* ============================
   MPI FUNCTION PROTOTYPES
   All functions are stubs with documentation.
   ============================ */

/**
 * @brief Initialize the MPI execution environment.
 */
int MPI_Init(int *argc, char ***argv);

/**
 * @brief Terminate the MPI execution environment.
 */
int MPI_Finalize(void);

/**
 * @brief Get the rank of the calling process in the communicator.
 */
int MPI_Comm_rank(MPI_Comm comm, int *rank);

/**
 * @brief Get the size of the communicator.
 */
int MPI_Comm_size(MPI_Comm comm, int *size);

/**
 * @brief Send a message to a given destination.
 */
int MPI_Send(const void *buf, int count, MPI_Datatype datatype,
             int dest, int tag, MPI_Comm comm);

/**
 * @brief Receive a message from a given source.
 */
int MPI_Recv(void *buf, int count, MPI_Datatype datatype,
             int source, int tag, MPI_Comm comm, MPI_Status *status);

/**
 * @brief Block until all processes reach this routine.
 */
int MPI_Barrier(MPI_Comm comm);

/**
 * @brief Broadcast a message from the root process to all others.
 */
int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype,
              int root, MPI_Comm comm);

/**
 * @brief Reduce values from all processes to root.
 */
int MPI_Reduce(const void *sendbuf, void *recvbuf, int count,
               MPI_Datatype datatype, int op, int root, MPI_Comm comm);

/**
 * @brief Reduce values and distribute the result to all processes.
 */
int MPI_Allreduce(const void *sendbuf, void *recvbuf, int count,
                  MPI_Datatype datatype, int op, MPI_Comm comm);

/* ============================
   NONBLOCKING OPERATIONS (optional)
   ============================ */

/**
 * @brief Nonblocking send.
 */
int MPI_Isend(const void *buf, int count, MPI_Datatype datatype,
              int dest, int tag, MPI_Comm comm, MPI_Request *req);

/**
 * @brief Nonblocking receive.
 */
int MPI_Irecv(void *buf, int count, MPI_Datatype datatype,
              int source, int tag, MPI_Comm comm, MPI_Request *req);

/**
 * @brief Wait for a nonblocking operation to complete.
 */
int MPI_Wait(MPI_Request *req, MPI_Status *status);

/**
* @brief Return an elapsed wall-clock time in seconds.
*/
double MPI_Wtime(void);

/**
 * @brief Distribute equal-sized blocks of data from the root to all processes.
 */
int MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
                void *recvbuf, int recvcount, MPI_Datatype recvtype,
                int root, MPI_Comm comm);

/**
 * @brief Abort all MPI processes in the given communicator.
 */
int MPI_Abort(MPI_Comm comm, int errorcode);


#ifdef __cplusplus
}
#endif

#endif // MPI_STUB_H
