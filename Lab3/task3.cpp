#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main() {
    int k;
    int N;

    scanf("%d %d", &k, &N);

    int total_sum = 0;

    #pragma omp parallel num_threads(k)
    {
        int tid = omp_get_thread_num();
        int partial_sum = 0;

        #pragma omp for
        for (int i = 1; i <= N; ++i) {
            partial_sum += i;
            printf("[%d] calculation of the iteration number %d\n", tid, i);

            #pragma omp atomic
            total_sum += i;
        }

        printf("[%d] calculation of the iteration number: Sum = %d\n", tid, partial_sum);
    }

    printf("Sum = %d\n", total_sum);
}
