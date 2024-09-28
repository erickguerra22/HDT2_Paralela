#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char message[100];
    char response[100];

    if (rank > 0) {
        printf("Hi, I'm process %d of %d and I'm sending!\n", rank, size);
        sprintf(message, "Sending message from process %d of %d to process 0!\n", rank, size);
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);

        MPI_Recv(response, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        printf("%s", response);        
    } else {
        printf("Hi, I'm process %d of %d and I'm receiving!\n", rank, size);
        for (int i = 1; i < size; i++) {
            MPI_Recv(message, 100, MPI_CHAR, i, 0, MPI_COMM_WORLD, &status);
            printf("%s", message);

            sprintf(response, "Hi, I'm process %d of %d and I'm sending a response to %d!\n", rank, size, i);
            MPI_Send(response, strlen(response) + 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }        
    }

    MPI_Finalize();

    return 0;
}
