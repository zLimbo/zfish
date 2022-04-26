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
    ThreadPool(int num) : mClose(false) {
        for (int i = 0; i < num; ++i) {
            std::thread th([this] {
                for (;;) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> locker(mMutex);
                        mCv.wait(locker, [this] {
                            return mClose || !mTaskQueue.empty();
                        });
                        if (mClose && mTaskQueue.empty()) {
                            std::cout << "thread " << std::this_thread::get_id()
                                      << " exit." << std::endl;
                            return;
                        }
                        task = std::move(mTaskQueue.front());
                        mTaskQueue.pop();
                    }
                    task();
                }
            });
            mWorkers.push_back(std::move(th));
        }
    }

    template <typename Func, typename... Args>
    auto put(Func&& func, Args&&... args)
        -> std::future<typename std::result_of<Func(Args...)>::type> {
        using ResultType = typename std::result_of<Func(Args...)>::type;
        auto task = std::make_shared<std::packaged_task<ResultType()>>(
            std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
        {
            std::unique_lock<std::mutex> locker(mMutex);
            if (mClose) {
                throw std::runtime_error("thread pool has closed!");
            }
            mTaskQueue.push([task] { (*task)(); });
        }
        mCv.notify_one();
        return task->get_future();
    }

    ~ThreadPool() { close(); }

    void close() {
        {
            std::lock_guard<std::mutex> locker(mMutex);
            if (mClose) return;
            mClose = true;
        }
        mCv.notify_all();
        for (std::thread& worker : mWorkers) {
            worker.join();
        }
    }

private:
    bool mClose = true;
    std::mutex mMutex;
    std::condition_variable mCv;
    std::vector<std::thread> mWorkers;
    std::queue<std::function<void()>> mTaskQueue;
};

#endif  // THREADPOOL_H