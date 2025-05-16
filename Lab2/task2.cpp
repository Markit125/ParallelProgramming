#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "../common/execution_time.cpp"


int main() {
    int n;
    printf("Enter vector size: ");
    scanf("%d", &n);

    double * A = (double *) malloc(n * sizeof(double));
    double * B = (double *) malloc(n * sizeof(double));

    for (int i = 0; i < n; i++) {
        A[i] = (double) rand() / RAND_MAX;
        B[i] = (double) rand() / RAND_MAX;
    }

    double seq_result = 0.0;
    double par_result = 0.0;

    ExecutionTime time_sequently = ExecutionTime();
    ExecutionTime time_parallel = ExecutionTime();

    time_sequently.start();

    for (int i = 0; i < n; i++) {
        seq_result += A[i] * B[i];
    }

    time_sequently.stop();

    time_parallel.start();

    #pragma omp parallel for reduction(+:par_result)
    for (int i = 0; i < n; i++) {
        par_result += A[i] * B[i];
    }

    time_parallel.stop();

    printf("\nSequently:  \t%.6f (time: %.6f ms)\n", seq_result, time_sequently.get_execution_time() * 1000);
    printf("Parallel:\t%.6f (time: %.6f ms)\n", par_result, time_parallel.get_execution_time() * 1000);
    printf("Speedup:\t%.2f\n", (time_sequently.get_execution_time()) / (time_parallel.get_execution_time()));

    free(A);
    free(B);

    return 0;
}

// Enter vector size: 10

// Sequently:      3.449990 (time: 0.000491 ms)
// Parallel:       3.449990 (time: 0.813802 ms)
// Speedup:        0.00

// Enter vector size: 1000

// Sequently:      255.735776 (time: 0.010203 ms)
// Parallel:       255.735776 (time: 5.679138 ms)
// Speedup:        0.00

// Enter vector size: 1000000

// Sequently:      250048.443177 (time: 2.208447 ms)
// Parallel:       250048.443177 (time: 3.551141 ms)
// Speedup:        0.62

// Enter vector size: 10000000

// Sequently:      2500484.299298 (time: 20.840553 ms)
// Parallel:       2500484.299298 (time: 5.580457 ms)
// Speedup:        3.73

// Enter vector size: 100000000

// Sequently:      25000639.975706 (time: 208.354904 ms)
// Parallel:       25000639.975712 (time: 54.814343 ms)
// Speedup:        3.80