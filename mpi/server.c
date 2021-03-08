#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
 
int size, rank, msg;
 
int main(int argc, char *argv[]) {
    MPI_Comm client;
    MPI_Status status;
    char port[MPI_MAX_PORT_NAME];
    
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


   // MPI_Publish_name("ocean", MPI_INFO_NULL, port);
    MPI_Open_port(MPI_INFO_NULL, port);
    
    printf("PORT: %s\n", port);

    MPI_Comm_accept(port, MPI_INFO_NULL, 0, MPI_COMM_SELF, &client);
    printf("client connected\n");

    MPI_Recv(&msg, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, client, &status);
    printf("msg: %d\n", msg);
    
    MPI_Comm_free(&client);
    MPI_Close_port(port);
    MPI_Finalize();
}