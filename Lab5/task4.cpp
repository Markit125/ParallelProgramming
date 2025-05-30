#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore.h>


void sleep() {
    std::this_thread::sleep_for(std::chrono::nanoseconds(rand()));
}

void think() {
    sleep();
}

void eat() {
    sleep();
}

const int philosopher_count = 5;
sem_t semaphores[philosopher_count];

std::mutex output_mx;

void philoshoper_action(int i) {
    int left_fork = i;
    int right_fork = (i + 1) % philosopher_count;

    sem_wait(&semaphores[left_fork]);
    sem_wait(&semaphores[right_fork]);

    output_mx.lock();
    std::cout << "Philosopher " << i << " eats with forks " << left_fork << " and " << right_fork << "\n";
    output_mx.unlock();

    eat();

    sem_post(&semaphores[left_fork]);
    sem_post(&semaphores[right_fork]);

    output_mx.lock();
    std::cout << "Philosopher " << i << " thinks" << "\n";
    output_mx.unlock();

    think();
}


void last_philoshoper_action(int i) {
    int left_fork = i;
    int right_fork = (i + 1) % philosopher_count;

    sem_wait(&semaphores[right_fork]);
    sem_wait(&semaphores[left_fork]);

    output_mx.lock();
    std::cout << "Philosopher " << i << " eats with forks " << left_fork << " and " << right_fork << "\n";
    output_mx.unlock();

    eat();

    sem_post(&semaphores[right_fork]);
    sem_post(&semaphores[left_fork]);

    output_mx.lock();
    std::cout << "Philosopher " << i << " thinks" << "\n";
    output_mx.unlock();

    think();
}

int main() {
    std::srand(time(nullptr));

    for (int i = 0; i < philosopher_count; ++i) {
        sem_init(&semaphores[i], 0, 1);
    }
    
    std::thread phisosophers[philosopher_count];

    for (int i = 0; i < philosopher_count - 1; ++i) {
        phisosophers[i] = std::thread(philoshoper_action, i);
    }

    phisosophers[philosopher_count - 1] = std::thread(last_philoshoper_action, philosopher_count - 1);

    for (int i = 0; i < philosopher_count; ++i) {
        if (phisosophers[i].joinable()) {
            phisosophers[i].join();
        }
    }

    std::cout << "All philosophers have eaten and thought\n";

    for (int i = 0; i < philosopher_count; ++i) {
        sem_destroy(&semaphores[i]);
    }

    return 0;
}
