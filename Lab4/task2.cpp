#include <stdio.h>
#include <omp.h>

int main() {
    int n = 20;
    int a[n], b[n];
    for (int i = 0; i < n; ++i) {
        a[i] = b[i] = i + 1;
    }

    #pragma omp parallel shared(a, b)
    {
        #pragma omp for nowait
        for (int i = 0; i < n - 1; i++) {
            a[i] = a[i + 1];
        }

        // #pragma omp barrier

        #pragma omp for nowait
        for (int i = 0; i < n; i++) {
            b[i] = a[i];
        }
    }

    for (int i = 0; i < n; ++i) {
        if (a[i] != b[i]) {
            printf("wrong output!\n");
        
            printf("Array a: ");
            for (int i = 0; i < n; ++i) printf("%d ", a[i]);
        
            printf("\nArray b: ");
            for (int i = 0; i < n; ++i) printf("%d ", b[i]);
            printf("\n");

            break;
        }
    }
    
    return 0;
}
