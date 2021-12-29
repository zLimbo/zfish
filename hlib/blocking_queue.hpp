#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include <condition_variable>
#include <mutex>
#include <queue>

namespace zfish {

template <typename T>
class BlockingQueue {
public:
    BlockingQueue(int max_size) : max_size_(max_size) {}
    BlockingQueue(const BlockingQueue&) = delete;
    BlockingQueue& operator=(const BlockingQueue&) = delete;

    template <typename... Args>
    void enqueue(Args&&... args) {
        std::unique_lock<std::mutex> locker(mtx_);
        not_full_.wait(locker, [this] { return queue_.size() < max_size_; });
        queue_.emplace(std::forward<Args>(args)...);
        not_empty_.notify_one();
    }

    T dequeue() {
        std::unique_lock<std::mutex> locker(mtx_);
        not_empty_.wait(locker, [this] { return queue_.size() > 0; });
        T x = std::move(queue_.front());
        queue_.pop();
        not_full_.notify_one();
        return x;
    }

    size_t size() {
        std::unique_lock<std::mutex> locker(mtx_);
        return queue_.size();
    }

private:
    size_t max_size_;
    std::queue<T> queue_;
    std::mutex mtx_;
    std::condition_variable not_empty_;
    std::condition_variable not_full_;
};

}  // namespace zfish

#endif  // BLOCKING_QUEUE_H