/**
 * @file AsyncLogger.h
 * @brief
 *
 * @version 1.0
 * @author Tianen Lu (tianenlu957@gmail.com)
 * @date 2022-11
 */


#ifndef ASYNCLOGGER_H
#define ASYNCLOGGER_H

#include "NonCopyable.h"
#include "Mutex.h"
#include "Thread.h"
#include "LogStream.h" // FixedBuffer

#include <atomic>
#include <vector>

namespace Lux {
class AsyncLogger : noncopyable {
private:
    void threadFunc();

    using Buffer = Lux::detail::FixedBuffer<Lux::detail::kLargeBuffer>;
    using BufferVector = std::vector<std::unique_ptr<Buffer>>;
    using BufferPtr = BufferVector::value_type;

    const int flushInterval_;
    std::atomic<bool> running_;
    const string basename_;
    const off_t rollSize_;
    Lux::Thread thread_;
    Lux::CountDownLatch latch_;
    Lux::MutexLock mutex_;
    Lux::Condition cond_ GUARDED_BY(mutex_);

    /// 当前缓冲
    BufferPtr currentBuffer_ GUARDED_BY(mutex_);
    /// 预备缓冲，相当于 currentBuffer_ 的“备胎”
    BufferPtr nextBuffer_ GUARDED_BY(mutex_);
    /// 待写入文件的已填满的缓冲
    BufferVector buffers_ GUARDED_BY(mutex_);

public:
    AsyncLogger(const string& basename, off_t rollSize, int flushInterval = 3);

    /// Destructor
    ~AsyncLogger() {
        if (running_) {
            stop();
        }
    }

    void append(const char* logline, int len);

    /// @brief start -
    ///  1. start thread
    ///  2. latch wait
    void start() {
        running_ = true;
        thread_.start();
        latch_.wait();
    }

    void stop() NO_THREAD_SAFETY_ANALYSIS {
        running_ = false;
        cond_.notify();
        thread_.join();
    }
};
} // namespace Lux
#endif // ASYNCLOGGER_H