#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "../common/execution_time.cpp"

#define LIMIT 100000

int main() {
    int n;
    int m;

    scanf("%d %d", &n, &m);

    int **matrix = (int **) malloc(sizeof(int *) * n);
    
    for (int i = 0; i < n; ++i) {
        matrix[i] = (int *) malloc(sizeof(int) * m);
    }

    int *row_sums_parallel = (int *) calloc(n, sizeof(int));
    int *row_sums_sequently = (int *) calloc(n, sizeof(int));

    srand(time(NULL));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = rand();
        }
    }

    int overall_sum_parallel = 0;
    int overall_sum_sequently = 0;

    ExecutionTime time_parallel = ExecutionTime();
    time_parallel.start();

    #pragma omp parallel for reduction(+:overall_sum_parallel) if(n > LIMIT)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            row_sums_parallel[i] += matrix[i][j];
            overall_sum_parallel += matrix[i][j];
        }
    }

    time_parallel.stop();

    ExecutionTime time_sequently = ExecutionTime();
    time_sequently.start();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            row_sums_sequently[i] += matrix[i][j];
            overall_sum_sequently += matrix[i][j];
        }
    }

    time_sequently.stop();

    for (int i = 0; i < n; i += n / 10) {
        printf("Row %d sum:\t%d\n    \t%d\n", i, row_sums_parallel[i], row_sums_sequently[i]);
    }

    printf("Overall sum parallel: %d\n                     %d\n", overall_sum_parallel, overall_sum_sequently);

    printf("time parallel:  %.6f ms\n", time_parallel.get_execution_time() * 1000);
    printf("time seqiently: %.6f ms\n", time_sequently.get_execution_time() * 1000);
    printf("Speedup:\t%.2f\n", (time_sequently.get_execution_time()) / (time_parallel.get_execution_time()));


    return 0;
}

// ❯ g++ -fopenmp Lab2/task3.cpp && ./a.out
// 100
// 100
// time parallel:  0.149545 ms
// time seqiently: 0.110333 ms
// Speedup:        0.74
// ❯ g++ -fopenmp Lab2/task3.cpp && ./a.out
// 1000 1000
// time parallel:  4.245862 ms
// time seqiently: 2.972522 ms
// Speedup:        0.70
// ❯ g++ -fopenmp Lab2/task3.cpp && ./a.out
// 10000 10000
// time parallel:  266.058097 ms
// time seqiently: 244.367325 ms
// Speedup:        0.92
// ❯ g++ -fopenmp Lab2/task3.cpp && ./a.out
// 50000 50000
// time parallel:  6712.660772 ms
// time seqiently: 6138.671331 ms
// Speedup:        0.91
// ❯ g++ -fopenmp Lab2/task3.cpp && ./a.out
// 100000 10000
// time parallel:  708.480724 ms
// time seqiently: 2473.289233 ms
// Speedup:        3.49
// ❯ g++ -fopenmp Lab2/task3.cpp && ./a.out
// 75000 5000
// time parallel:  990.602760 ms
// time seqiently: 913.942628 ms
// Speedup:        0.92