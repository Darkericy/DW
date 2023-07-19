#pragma once

#include <string.h>
#include <assert.h>
#include <exception>
#include <boost/lexical_cast.hpp>

#include "log.h"

/// 断言宏封装
template<class T> 
void inline DW_ASSERT(const T& x){
    try{
        if(!x){
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
        if(!x){
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