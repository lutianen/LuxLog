# Test LuxLogger library
add_executable(LuxLoggerTest LuxLogger_test.cc)
target_link_libraries(LuxLoggerTest LuxLogger)

add_executable(AtomicTest Atomic_unittest.cc)
target_link_libraries(AtomicTest LuxLogger)

add_executable(TimestampUnittest Timestamp_unittest.cc)
target_link_libraries(TimestampUnittest LuxLogger)

add_executable(ThreadTest Thread_test.cc)
target_link_libraries(ThreadTest LuxLogger)

add_executable(ExceptionTest Exception_test.cc)
target_link_libraries(ExceptionTest LuxLogger)

add_executable(FileUitlTest FileUtil_test.cc)
target_link_libraries(FileUitlTest LuxLogger)

add_executable(MutexTest Mutex_test.cc)
target_link_libraries(MutexTest LuxLogger)

add_executable(ProcessInfoTest ProcessInfo_test.cc)
target_link_libraries(ProcessInfoTest LuxLogger)

