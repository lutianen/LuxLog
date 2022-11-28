/**
 * @file ProcessInfo.h
 * @brief
 *
 * @version 1.0
 * @author Tianen Lu (tianenlu957@gmail.com)
 * @date 2022-11
 */

#ifndef PROCESSINFO_H
#define PROCESSINFO_H

#include "Types.h"
#include "Timestamp.h"
#include "StringPiece.h"

#include <sys/types.h> // pid_t
#include <vector>      // vector

namespace Lux {
namespace ProcessInfo {
    pid_t pid();
    string pidString();
    uid_t uid();
    string username();
    uid_t euid();
    Timestamp startTime();
    int clockTicksPerSecond();
    int pageSize();
    bool isDebugBuild(); // constexpr

    string hostname();
    string procname();
    StringPiece procname(const string& stat);

    /// read /proc/self/status
    string procStatus();

    /// read /proc/self/stat
    string procStat();

    /// read /proc/self/task/tid/stat
    string threadStat();

    /// readlink /proc/self/exe
    string exePath();

    int openedFiles();
    int maxOpenFiles();

    struct CpuTime {
        double userSeconds;
        double systemSeconds;

        CpuTime() : userSeconds(0.0), systemSeconds(0.0) {}

        double total() const { return userSeconds + systemSeconds; }
    };
    CpuTime cpuTime();

    int numThreads();
    std::vector<pid_t> threads();
} // namespace ProcessInfo
} // namespace Lux
#endif // PROCESSINFO_H
