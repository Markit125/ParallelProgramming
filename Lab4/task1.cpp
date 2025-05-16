#include <stdio.h>
#include <omp.h>

int main() {
    int n;
    scanf("%d", &n);

    int sum = 0;

    #pragma omp parallel shared(sum), num_threads(n)
    {
        #pragma omp atomic
        sum += 1;
    }

    printf("Sum = %d\n", sum);
    return 0;
}
