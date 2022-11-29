# Test LuxLog library
add_executable(LuxLogTest LuxLog_test.cc)
target_link_libraries(LuxLogTest LuxLog)

add_executable(AtomicTest Atomic_unittest.cc)
target_link_libraries(AtomicTest LuxLog)

add_executable(TimestampUnittest Timestamp_unittest.cc)
target_link_libraries(TimestampUnittest LuxLog)

add_executable(ThreadTest Thread_test.cc)
target_link_libraries(ThreadTest LuxLog)

add_executable(ExceptionTest Exception_test.cc)
target_link_libraries(ExceptionTest LuxLog)

add_executable(FileUitlTest FileUtil_test.cc)
target_link_libraries(FileUitlTest LuxLog)

add_executable(MutexTest Mutex_test.cc)
target_link_libraries(MutexTest LuxLog)

add_executable(ProcessInfoTest ProcessInfo_test.cc)
target_link_libraries(ProcessInfoTest LuxLog)

add_executable(LuxINITest LuxINI_test.cc)
target_link_libraries(LuxINITest LuxLog)
