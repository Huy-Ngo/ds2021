#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
int size, rank;
int main(int argc, char *argv[]) {
    MPI_Comm server;
    int msg, tag, dest;
    char port[MPI_MAX_PORT_NAME]; 
    
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (argc >= 2) {
        printf("Connecting to %s\n", argv[1]);
        strcpy(port, argv[1]);
        
        MPI_Comm_connect(port, MPI_INFO_NULL, 0, MPI_COMM_SELF, &server);

        msg = 42; tag = 0; dest = 0;

        MPI_Send(&msg, 1, MPI_INT, dest, tag, server);

        MPI_Comm_disconnect(&server);
    }
    MPI_Finalize();
}