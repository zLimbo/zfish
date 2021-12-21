#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>

template <typename T>
class BlockingQueue {
public:
    BlockingQueue(int maxSize) : mMaxSize(maxSize) {}

    template <typename... Args>
    void put(Args&&... args) {
        std::unique_lock locker(mMutex);
        mNotFullCV.wait(locker, [&] { return mQueue.size() < mMaxSize; });
        mQueue.emplace(std::forward<Args>(args)...);
        mNotEmptyCV.notify_one();
    }

    T take() {
        std::unique_lock locker(mMutex);
        mNotEmptyCV.wait(locker, [&] { return mQueue.size() > 0; });
        T&& x = std::move(mQueue.front());
        mQueue.pop();
        mNotFullCV.notify_one();
        return x;
    }

    T& front() {
        std::lock_guard locker(mMutex);
        return mQueue.front();
    }

    size_t size() {
        std::lock_guard locker(mMutex);
        return mQueue.size();
    }

private:
    int mMaxSize;
    std::mutex mMutex;
    std::condition_variable mNotFullCV;
    std::condition_variable mNotEmptyCV;
    std::queue<T> mQueue;
};

#endif  // BLOCKINGQUEUE_H