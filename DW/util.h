#pragma once
#include <iostream>
#include <thread>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

namespace DW
{
    uint32_t GetThreadId();
    uint32_t GetFiberId();
} // namespace DW
