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
} // namespace DW
