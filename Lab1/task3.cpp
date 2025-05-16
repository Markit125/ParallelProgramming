#include <stdio.h>
#include "../common/execution_time.cpp"

int main()
{
    ExecutionTime time = ExecutionTime();

    int n = 100000, i;
    double pi, h, sum, x;
    h = 1.0 / (double) n;
    sum = 0.0;

    time.start();

    #pragma omp parallel
    {
        #pragma omp for schedule(static)
            for (i = 1; i <= n; i ++) {
                x = h * ((double)i - 0.5);
                sum += (4.0 / (1.0 + x*x));
            }
    
    }

    pi = h * sum;
    
    time.stop();

    printf("pi is approximately %.16f", pi);

    printf("time = %f", time.get_execution_time());

    return 0;
}
