#include <mpi.h>
#include <stdlib.h>
#include <iostream>
#include <queue>

#define REQ_K 1
#define ACK_K 2

struct request{
        int rank;
        int priority;
};

std::queue<request> req_k;

int main(int argc, char **argv)
{
        int rank, size, zm;
    MPI_Status status;
        int vector[4] = {0, 0, 0, 0};

        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        int tmp = 1;
        while (tmp)
        {
                request my_req = {.rank = rank, .priority = vector[rank]};
                request other_req;
                for(int i = 0; i < size; i++){
                        MPI_Send(&my_req, sizeof(struct request), MPI_BYTE, i, REQ_K, MPI_COMM_WORLD);
                        MPI_Recv(&other_req, sizeof(struct request), MPI_BYTE, i, REQ_K, MPI_COMM_WORLD, &status);
                        req_k.push(other_req);
                        if(rank == 0){
                                printf("%d %d\n", other_req.rank, other_req.priority);
                        }
                }
                tmp--;
        }

        MPI_Finalize();
}
