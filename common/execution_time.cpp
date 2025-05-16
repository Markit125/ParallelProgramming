#include <omp.h>

class ExecutionTime {
private:
    double start_time;
    double execution_time;

public:
    void start() {
        start_time = omp_get_wtime();
    }

    void stop() {
        execution_time = omp_get_wtime() - start_time;
    }

    double get_execution_time() {
        return execution_time;
    }
};
