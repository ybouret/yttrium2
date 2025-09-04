#include <mpi.h>
#include <cstdlib>

int main(int argc, char **argv)
{
	if(MPI_SUCCESS != MPI_Init(&argc,&argv) ) abort();

	MPI_Finalize();
	return 0;
}
