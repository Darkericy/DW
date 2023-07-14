#include "util.h"

namespace DW{
    uint32_t GetThreadId(){
        return (pid_t)syscall(__NR_gettid);
    }
    uint32_t GetFiberId(){
        return 0;   //暂时返回0
    }
}