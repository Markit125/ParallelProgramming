#include <stdio.h>
#include <omp.h>
#include "../common/execution_time.cpp"

int main() {
    int num_threads;
    scanf("%d", &num_threads);

    ExecutionTime time = ExecutionTime();
    time.start();

    #pragma omp parallel num_threads(num_threads)
    {
        #pragma omp for schedule(static)
            for (int n = 0; n < 10; ++n) {
                printf("I'm thread %d, i = %d\n", omp_get_thread_num(), n);
            }
    }

    time.stop();

    printf("time = %f", time.get_execution_time());
}
