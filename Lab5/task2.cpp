#include <iostream>
#include <mutex>
#include <thread>

std::mutex g_lock;

void timeSleep() {
    std::thread::id id = std::this_thread::get_id();

    g_lock.lock();
    
    std::cout << "Thread with id " << id << " started\n";
    std::cout << "Thread with id " << id << " finished\n";

    g_lock.unlock();
    
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
    const int length = 5;
    std::thread thread_array[length];

    for (int i = 0; i < length; i++) {
        thread_array[i] = std::thread(timeSleep);
    }

    for (int i = 0; i < length; i++) {
        if (thread_array[i].joinable()) {
            thread_array[i].join();
        }
    }

    return 0;
}
