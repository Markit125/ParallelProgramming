#include <mutex>
#include <thread>

static int counter = 0;
std::mutex mx;

void worker1() {
    int local;

    for (int i = 0; i < 100; i++) {
        mx.lock();

        local = counter;
        printf("worker1 - %d\n", local);
        local++;
        counter = local;

        mx.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void worker2() {
    int local;

    for (int i = 0; i < 100; i++) {
        mx.lock();

        local = counter;
        printf("worker2 - %d\n", local);
        local--;
        counter = local;

        mx.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main() {
    std::thread thread1(worker1);
    std::thread thread2(worker2);

    if (thread1.joinable())
        thread1.join();
    if (thread2.joinable())
        thread2.join();

    printf(" == %d\n", counter);
}
