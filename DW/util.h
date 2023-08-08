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
    static bool IsRunningPidfile(const std::string& pidfile);
    static bool Mkdir(const std::string& dirname);
    static bool Rm(const std::string& path);
    static bool Mv(const std::string& from, const std::string& to);
    static bool Realpath(const std::string& path, std::string& rpath);
    static bool Symlink(const std::string& frm, const std::string& to);
    static bool Unlink(const std::string& filename, bool exist = false);
    static std::string Dirname(const std::string& filename);
    static std::string Basename(const std::string& filename);
    static bool OpenForRead(std::ifstream& ifs, const std::string& filename
                    ,std::ios_base::openmode mode);
    static bool OpenForWrite(std::ofstream& ofs, const std::string& filename
                    ,std::ios_base::openmode mode);
};
} // namespace DW
