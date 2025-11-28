#include <stdio.h>

#ifdef _WIN32
#include "mpi_stub.h"
#else
#include <mpi.h>
#endif


int main(int argc, char **argv) {

    return 0;
}
