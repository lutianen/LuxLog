// Required headers
#include "src/AsyncLogger.h"
#include "src/Logger.h"

#include <cstdio>
#include <sys/resource.h>
#include <unistd.h>


// Global logger.
Lux::AsyncLogger* g_asyncLog = nullptr;


int main(int argc, char** argv) {
    {
        // Optional: set max virtual memory to 2GB.
        size_t kOneGB = 1000 * 1024 * 1024;

        rlimit rl = {2 * kOneGB, 2 * kOneGB};
        setrlimit(RLIMIT_AS, &rl);
    }

    char name[] = "test";
    off_t rollSize = 500 * 1000 * 1000;
    int flushInterval = 1;

    Lux::AsyncLogger log(::basename(name), rollSize, flushInterval);

    // Set level of logger
    Lux::Logger::setLogLevel(Lux::Logger::LogLevel::TRACE);

    // set output Func, or use defalut.
    Lux::Logger::setOutput([](const char* msg, int len) {
        size_t n = ::fwrite(msg, 1, static_cast<size_t>(len), stdout);
        assert(n == static_cast<size_t>(len));
        if (n != static_cast<size_t>(len)) {
            char _buf[128] = {};
            ::snprintf(
                _buf, sizeof(_buf), "%s : %d - n should be equal len!!!", __FILE__, __LINE__);
            ::perror(_buf);
        }

        g_asyncLog->append(msg, len);
    });
    g_asyncLog = &log;
    log.start();

    LOG_TRACE << "This is log TRACE TEST";
    LOG_DEBUG << "This is log DEBUG TEST";
    LOG_INFO << "This is log INFO TEST";
    LOG_WARN << "This is log WARN TEST";
    LOG_ERROR << "This is log ERROR TEST";
    LOG_SYSERR << "This is log SYSERR TEST";

    /* Wait backend thread write logs into file.
     * Only needed when testing LuxLogger.
     */
    usleep(5000);
}
