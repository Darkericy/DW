#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <execinfo.h>

namespace DW
{
    uint32_t GetThreadId();
    uint32_t GetFiberId();

    void Backtrace(std::vector<std::string>& bt, int size = 64, int skip = 1);

    std::string BacktraceToString(int size = 64, int skip = 2, const std::string& prefix = "");

    //获取当前的毫秒
    uint64_t GetCurrentMS();

    //获取当前的微秒
    uint64_t GetCurrentUS();

    std::string Time2Str(time_t ts = time(0), const std::string& format = "%Y-%m-%d %H:%M:%S");
    time_t Str2Time(const char* str, const char* format = "%Y-%m-%d %H:%M:%S");

struct FSUtil{
    static void ListAllFile(std::vector<std::string>& files
                            ,const std::string& path
                            ,const std::string& subfix);
};
} // namespace DW
