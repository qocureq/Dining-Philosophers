//  This solution is using 'naive' method, where each philosopher picks up the fork on his left, and then on his right.
//  If fork cannot be picked up, he waits for the other philosopher to finish eating.
//  Note that, this solution can enter a state, where all philosophers picked up their left fork at the same time, it
//  can enter a state, where no action is made since all of them are waiting their right forks resulting in deadlock.

#include "../include/naive.hpp"

Naive::Naive(int id, std::shared_ptr<Fork> left, std::shared_ptr<Fork> right)
        : Philosopher(id, std::move(left), std::move(right)) {};

void Naive::eat() {
    auto start = std::chrono::high_resolution_clock::now();
    std::lock_guard<std::mutex> lck(leftFork->mutex);
    std::lock_guard<std::mutex> rck(rightFork->mutex);
    auto end = std::chrono::high_resolution_clock::now();
    waitingTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    status("is eating");
    meals++;
    std::this_thread::sleep_for(10ms);
}

Naive::~Naive() {
    stop();
    if (thr.joinable()) {
        thr.join();
    }
    enableStatusMessages();
    status("ate " + std::to_string(meals) + " times. Average waiting time = " + std::to_string(waitingTime / meals) +
           "ms");
}