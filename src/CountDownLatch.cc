/**
 * @file CountDhownLatch.cc
 * @brief
 *
 * @version 1.0
 * @author Tianen Lu (tianenlu957@gmail.com)
 * @date 2022-11
 */

#include "CountDownLatch.h"

Lux::CountDownLatch::CountDownLatch(int count) : mutex_(), condition_(mutex_), count_(count) {}


void Lux::CountDownLatch::wait() {
    Lux::MutexLockGuard lock(mutex_);
    while (count_ > 0) {
        condition_.wait();
    }
}


void Lux::CountDownLatch::countDown() {
    MutexLockGuard lock(mutex_);
    --count_;
    if (count_ == 0) {
        condition_.notifyAll();
    }
}

int Lux::CountDownLatch::getCount() const {
    MutexLockGuard lock(mutex_);
    return count_;
}
