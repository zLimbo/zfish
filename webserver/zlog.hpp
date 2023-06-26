#ifndef ZLOG_H
#define ZLOG_H

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "../hlib/zfish.hpp"

#define Log zlog::Stream(__FILE__, __LINE__)

namespace zlog {

class Util {
public:
    static std::string GetDateTime() {
        auto now = std::chrono::system_clock::now();
        auto as_time_t = std::chrono::system_clock::to_time_t(now);
        struct tm tm;
        localtime_r(&as_time_t, &tm);
        auto ms = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch());
        char buf[128];
        snprintf(buf, sizeof(buf), "%04d-%02d-%02d.%02d:%02d:%02d.%03ld", tm.tm_year + 1900,
                 tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, ms.count() % 1000);
        return buf;
    }
};

class Stream {
public:
    using self = Stream;
    Stream(std::string_view file, int line_no) {
        ss_ << Util::GetDateTime() << "|" << file << ":" << line_no << "|";
    }

    template <typename T>
    self& operator<<(T&& x) {
        ss_ << x;
        return *this;
    }

    ~Stream() {
        std::string s = ss_.str();
        ZLog::getInstance().Append(std::move(s));
    }

private:
    std::stringstream ss_;
};

class ZLog : zfish::Singleton<ZLog> {
public:
    constexpr static int kBufferSize = 100;
    constexpr static int kBufferBqSize = 10;
    constexpr static int kMsWait = 10;

    ZLog() : stop_{false} {
        curbuf_.reserve(kBufferSize);
        bakbuf_.reserve(kBufferSize);

        th_ = new std::thread {
            [this] {
                auto ms = std::chrono::milliseconds{kMsWait};
                while (true) {
                    std::vector<std::string> out_bufs;
                    {
                        std::unique_lock<std::mutex> locker{this->mu_};
                        this->cond_.wait_for(locker, ms,
                                             [&bufs = this->bufs_] { return !bufs.empty(); });
                        if (bufs_.empty() && stop_) {
                            break;
                        }
                        out_bufs = move(bufs_);
                    }
                    for (auto& buf : out_bufs) {
                        for (string& log : buf) {
                            cout << log << endl;
                        }
                    }
                }
            };
        };
    }

    ~ZLog() {
        stop_ = true;
        th_->join();
    }

    void Append(string msg) {
        if (stop_)
            return;
        curbuf_.push_back(move(msg));
        if (curbuf_.size() < kBufferSize) {
            return;
        }
        std::unique_lock<std::mutex> locker{mu_};
        bufs_.push_back(move(curbuf_));
        curbuf_.swap(bakbuf_);
        curbuf_.clear();
        curbuf_.reserve(kBufferSize);
    }

private:
    std::mutex mu_;
    std::condition_variable cond_;
    std::vector<std::string> curbuf_;
    std::vector<std::string> bakbuf_;
    std::vector<std::string> bufs_;
    std::unique_ptr<std::thread> th_;
    std::atomic_bool stop_;
};

}  // namespace zlog

#endif  // ZLOG_H