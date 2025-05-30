#include <iostream>
#include <thread>

void anyFunc1() {
    std::cout << "thread function 1\n";
}

void anyFunc2() {
    std::cout << "thread function 2\n";
}

int main() {
    std::thread func_thread_one(anyFunc1);
    std::thread func_thread_two(anyFunc2);

    if (func_thread_one.joinable()) {
        func_thread_one.join();
    }
    if (func_thread_two.joinable()) {
        func_thread_two.join();
    }
}
