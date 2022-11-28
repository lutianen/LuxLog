/**
 * @file LogFile.h
 * @brief
 *
 * @version 1.0
 * @author Tianen Lu (tianenlu957@gmail.com)
 * @date 2022-11
 */


#ifndef LOGFILE_H
#define LOGFILE_H

#include "Types.h"
#include "Mutex.h"

#include <memory>

namespace Lux {
namespace FileUtil {
    class AppendFile;
} // namespace FileUtil



class LogFile : noncopyable {
private:
    void append_unlocked(const char* logline, int len);

    static string getLogFileName(const string& basename, time_t* now);

    const string basename_;
    const off_t rollSize_;
    const int flushInterval_;
    const int checkEveryN_;

    int count_;

    std::unique_ptr<MutexLock> mutex_;
    time_t startOfPeriod_;
    time_t lastRoll_;
    time_t lastFlush_;
    std::unique_ptr<FileUtil::AppendFile> file_;

    const static int kRollPerSeconds_ = 60 * 60 * 24;

public:
    LogFile(const string& basename, off_t rollSize, bool threadSafe = true, int flushInterval = 3,
            int checkEveryN = 1024);
    ~LogFile();

    void append(const char* logline, int len);
    void flush();
    bool rollFile();
};

} // namespace Lux
#endif // LOGFILE_H