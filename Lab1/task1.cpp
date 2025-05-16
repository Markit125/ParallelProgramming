#include <stdio.h>
#include <omp.h>
#include "../common/execution_time.cpp"

int main() {
    int num_threads;
    scanf("%d", &num_threads);

    ExecutionTime time = ExecutionTime();

    int size;
    int rank;

    time.start();

    #pragma omp parallel private(size, rank) num_threads(num_threads)
    {
        rank = omp_get_thread_num();
        printf("I'm thread %d\n", rank);

        if (rank == 0) {
            size = omp_get_num_threads();
            printf("Number of threads = %d\n", size);
        }
    }

    printf("time = %f", time.get_execution_time());

    return 0;
}
