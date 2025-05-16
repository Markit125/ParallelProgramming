#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main() {

    int k;
    int n;

    scanf("%d %d", &k, &n);

    int total_sum = 0;

    #pragma omp parallel num_threads(k)
    {
        int tid = omp_get_thread_num();
        int partial_sum = 0;

        #pragma omp for reduction(+:total_sum)
        for (int i = 1; i <= n; ++i) {
            partial_sum += i;
            total_sum += i;
        }

        printf("[%d]: Sum = %d\n", tid, partial_sum);
    }

    printf("Sum = %d\n", total_sum);
}
