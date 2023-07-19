#include "util.h"
#include "log.h"
#include "fiber.h"

namespace DW{
    Logger::ptr g_logger = DW_LOG_NAME("system");

    uint32_t GetThreadId(){
        return (pid_t)syscall(__NR_gettid);
    }
    uint32_t GetFiberId(){
        //return 0;
        return Fiber::GetFiberId();
    }

    void Backtrace(std::vector<std::string>& bt, int size, int skip) {
        //堆上创建空间
        void** array = (void**)malloc((sizeof(void*) * size));
        size_t s = ::backtrace(array, size);

        char** strings = backtrace_symbols(array, s);
        if(strings == nullptr) {
            DW_LOG_ERROR(g_logger, __FILE__, __LINE__, TOSTRING("backtrace_synbols error"));
            free(array);
            return;
        }

        for(size_t i = skip; i < s; ++i) {
            bt.push_back(strings[i]);
        }

        free(strings);
        free(array);
    }

    std::string BacktraceToString(int size, int skip, const std::string& prefix) {
        std::vector<std::string> bt;
        Backtrace(bt, size, skip);
        std::stringstream ss;
        for(size_t i = 0; i < bt.size(); ++i) {
            ss << prefix << bt[i] << std::endl;
        }
        return ss.str();
    }
}