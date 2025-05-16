#include <stdio.h>
#include <omp.h>

int main() {
    int num_threads, n;

    printf("Enter thread count: ");
    scanf("%d", &num_threads);

    printf("Enter iteration count n: ");
    scanf("%d", &n);

    omp_set_num_threads(num_threads);

    #pragma omp parallel
    {
        #pragma omp for schedule(static)
        for (int i = 0; i < n; i++) {
            printf("I'm thread = %d, i = %d\n", omp_get_thread_num(), i);
        }
    }

    return 0;
}
