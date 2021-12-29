#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

class ThreadPool {
public:
    ThreadPool(int num) : close_(false) {
        for (int i = 0; i < num; ++i) {
            std::thread th([this] {
                for (;;) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> locker(mutex_);
                        cond_.wait(locker, [this] {
                            return close_ || !task_queue_.empty();
                        });
                        if (close_ && task_queue_.empty()) {
                            std::cout << "thread " << std::this_thread::get_id()
                                      << " exit." << std::endl;
                            return;
                        }
                        task = std::move(task_queue_.front());
                        task_queue_.pop();
                    }
                    task();
                }
            });
            workers_.push_back(std::move(th));
        }
    }

    template <typename Func, typename... Args>
    auto put(Func&& func, Args&&... args)
        -> std::future<typename std::result_of<Func(Args...)>::type> {
        using ResultType = typename std::result_of<Func(Args...)>::type;
        auto task = std::make_shared<std::packaged_task<ResultType()>>(
            std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
        {
            std::unique_lock<std::mutex> locker(mutex_);
            if (close_) {
                throw std::runtime_error("thread pool has closed!");
            }
            task_queue_.push([task] { (*task)(); });
        }
        cond_.notify_one();
        return task->get_future();
    }

    ~ThreadPool() { close(); }

    void close() {
        {
            std::lock_guard<std::mutex> locker(mutex_);
            if (close_) return;
            close_ = true;
        }
        cond_.notify_all();
        for (std::thread& worker : workers_) {
            worker.join();
        }
    }

private:
    bool close_ = true;
    std::mutex mutex_;
    std::condition_variable cond_;
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> task_queue_;
};

#endif  // THREADPOOL_H