#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <omp.h>
#include <utility>
#include "../common/execution_time.cpp"

void printArray(int *a, int len) {
    for (int i = 0; i < len; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void qsort(int *a, int n) {
    int i = 0;
    int j = n - 1;
    int pivot = a[n / 2];
    
    while (i < j) {
        while (a[i] < pivot) {
            ++i;
        }

        while (pivot < a[j]) {
            --j;
        }

        if (i <= j) {
            std::swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    
    #pragma omp task shared(a)
    {
        if (n - i > 1) {
            qsort(a + i, n - i);
        }
    }

    #pragma omp task shared(a)
    {
        if (j + 1 > 1) {
            qsort(a, j + 1);
        }
    }

    #pragma omp taskwait
}

int main() {
    int n;
    scanf("%d", &n);

    int *a = (int *) malloc(sizeof(int) * n);
    srand(time(nullptr));

    for (int i = 0; i < n; ++i) {
        a[i] = rand() % 1000;
    }

    printf("Initial array:\n");
    printArray(a, n);

    ExecutionTime time = ExecutionTime();
    time.start();

    #pragma omp parallel shared(a)
    {
        #pragma omp single nowait
        {
            qsort(a, n);
        }
    }

    time.stop();

    printf("Sorted array:\n");
    printArray(a, n);

    printf("Elapsed time: %.6f ms\n", time.get_execution_time() / 1000);

    return 0;
}
