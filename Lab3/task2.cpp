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

        #pragma omp for schedule(guided, 2) reduction(+:total_sum)
        for (int i = 1; i <= N; ++i) {
            partial_sum += i;
            total_sum += i;
            printf("[%d] calculation of the iteration number %d\n", tid, i);
        }


        printf("[%d] calculation of the iteration number: Sum = %d\n", tid, partial_sum);
    }

    printf("Sum = %d\n", total_sum);
}

// #========================================================================================#
// | Iteration │ static │ static, 1 │ static, 2 │ dynamic │ dynamic, 2 │ guided │ guided, 2 |
// #========================================================================================#
// |     1     │   0    │     0     │     0     │    0    │     0      │   0    │     0     |
// |     2     │   0    │     1     │     0     │    0    │     0      │   0    │     0     |
// |     3     │   0    │     2     │     1     │    1    │     1      │   0    │     0     |
// |     4     │   1    │     3     │     1     │    3    │     2      │   1    │     1     |
// |     5     │   1    │     0     │     2     │    0    │     1      │   2    │     1     |
// |     6     │   1    │     1     │     2     │    0    │     1      │   3    │     3     |
// |     7     │   2    │     2     │     3     │    0    │     0      │   3    │     3     |
// |     8     │   2    │     3     │     3     │    3    │     0      │   1    │     2     |
// |     9     │   3    │     0     │     0     │    0    │     0      │   0    │     2     |
// |    10     │   3    │     1     │     0     │    0    │     0      │   0    │     0     |
// #========================================================================================#
