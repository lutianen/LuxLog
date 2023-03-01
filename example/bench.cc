// Required headers
#include "src/AsyncLogger.h"
#include "src/Logger.h"

#include <iostream>
#include <sys/resource.h>
#include <unistd.h>
#include <ctime>

// Global logger.
Lux::AsyncLogger* g_asyncLog = nullptr;

void test_performance() {
    auto t = clock();
    for (int k = 0; k < 100; k++)
        for (int i = 0; i < 10000; ++i)
            LOG_INFO << "ABCEDFGHIJKLMNOPQRSTUVWXYZabcdefghijklmbopqrstvuwxyz1234567890"
                            "ABCEDFGHIJKLMNOPQRSTUVWXYZabcdefghijklmbopqrstvuwxyz1234567890"
                                "ABCEDFGHIJKLMNOPQRSTUVWXYZabcdefghijklmbopqrstvuwxyz1234567890"
                                "12345678901";

    std::cout << static_cast<double>(clock() - t)/CLOCKS_PER_SEC*1000 << "ms" << std::endl;
}


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
        g_asyncLog->append(msg, len);
    });
    g_asyncLog = &log;
    log.start();

    printf("pid=%d, tid=%d\n", ::getpid(), Lux::CurrentThread::tid());

    Lux::Thread t1(test_performance);
    Lux::Thread t2(test_performance);
    Lux::Thread t3(test_performance);
    Lux::Thread t4(test_performance);
    Lux::Thread t5(test_performance);
    Lux::Thread t6(test_performance);
    Lux::Thread t7(test_performance);

    t1.start();
    t2.start();
    t3.start();
    t4.start();
    t5.start();
    t6.start();
    t7.start();

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
}
