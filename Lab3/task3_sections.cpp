#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int k;

    scanf("%d", &k);

    #pragma omp parallel num_threads(k)
    {
        int tid = omp_get_thread_num();
        printf("[%d]: parallel region\n", tid);

        #pragma omp sections
        {
            #pragma omp section
            {
                printf("[%d]: came in section 1\n", omp_get_thread_num());
            }
            #pragma omp section
            {
                printf("[%d]: came in section 2\n", omp_get_thread_num());
            }
            #pragma omp section
            {
                printf("[%d]: came in section 3\n", omp_get_thread_num());
            }
        }
    }
}

// ❯ g++ -fopenmp Lab3/task3_sections.cpp && ./a.out
// 2
// [0]: parallel region
// [0]: came in section 1
// [0]: came in section 2
// [0]: came in section 3
// [1]: parallel region
// ❯ g++ -fopenmp Lab3/task3_sections.cpp && ./a.out
// 3
// [0]: parallel region
// [0]: came in section 1
// [0]: came in section 2
// [0]: came in section 3
// [2]: parallel region
// [1]: parallel region
// ❯ g++ -fopenmp Lab3/task3_sections.cpp && ./a.out
// 4
// [0]: parallel region
// [0]: came in section 1
// [0]: came in section 2
// [0]: came in section 3
// [3]: parallel region
// [1]: parallel region
// [2]: parallel region