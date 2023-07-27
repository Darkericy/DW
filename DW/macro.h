#pragma once

#include <string.h>
#include <assert.h>
#include <exception>
#include <boost/lexical_cast.hpp>

#include "log.h"

#if defined __GNUC__ || defined __llvm__
/// LIKCLY 宏的封装, 告诉编译器优化,条件大概率成立
#   define DW_LIKELY(x)       __builtin_expect(!!(x), 1)
/// LIKCLY 宏的封装, 告诉编译器优化,条件大概率不成立
#   define DW_UNLIKELY(x)     __builtin_expect(!!(x), 0)
#else
#   define DW_LIKELY(x)      (x)
#   define DW_UNLIKELY(x)      (x)
#endif

/// 断言宏封装
template<class T> 
void inline DW_ASSERT(const T& x){
    try{
        if(DW_UNLIKELY(!x)){
            DW::DW_LOG_ERROR(DW::DW_LOG_ROOT(), __FILE__, __LINE__, DW::TOSTRING(
                "ASSERTION: ",  boost::lexical_cast<std::string>(x),
                "\nbacktrace:\n", 
                DW::BacktraceToString(100, 2, "    ")
            ));
            assert(x);
        }
    }
    catch(std::exception& e){
        std::ostringstream os;
        os << "ASSERT exception "
        << e.what() <<  " convert: " << typeid(x).name() << " to string";
        DW::DW_LOG_ERROR(DW::DW_LOG_ROOT(), __FILE__, __LINE__, os.str());
    }
}

/// 断言宏封装
template<class T, class L> 
void inline DW_ASSERT(const T& x, const L& w){
    try{
        if(DW_UNLIKELY(!x)){
            DW::DW_LOG_ERROR(DW::DW_LOG_ROOT(), __FILE__, __LINE__, DW::TOSTRING(
                "ASSERTION: ",  boost::lexical_cast<std::string>(x),
                "\n",  boost::lexical_cast<std::string>(w),
                "\nbacktrace:\n", 
                DW::BacktraceToString(100, 2, "    ")
            ));
            assert(x);
        }
    }
    catch(std::exception& e){
        std::ostringstream os;
        os << "ASSERT exception "
        << e.what() <<  " convert: " << typeid(x).name() << " to string"
        << typeid(w).name() << " to string";
        DW::DW_LOG_ERROR(DW::DW_LOG_ROOT(), __FILE__, __LINE__, os.str());
    }
}