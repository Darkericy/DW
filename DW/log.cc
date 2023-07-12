#include "log.h"

namespace DW{
    void Logger::debug(LogLevel::Level level, LogEvent::ptr event){
        log(level, event);
    }
    void Logger::info(LogLevel::Level level, LogEvent::ptr event){
        log(level, event);
    }
    void Logger::warn(LogLevel::Level level, LogEvent::ptr event){
        log(level, event);
    }
    void Logger::error(LogLevel::Level level, LogEvent::ptr event){
        log(level, event);
    }
    void Logger::fatal(LogLevel::Level level, LogEvent::ptr event){
        log(level, event);
    }

    void Logger::log(LogLevel::Level level, LogEvent::ptr event){
        if(level >= m_level){
            for(const auto& app: m_appender){
                app->log(level, event);
            }
        }
    }

        //设置和返回等级
    LogLevel::Level Logger::getLevel(){
        return m_level;
    }
    void Logger::setLevel(LogLevel::Level level){
        m_level = level;
    }

        //插入和删除输出地
    void Logger::insertAppender(LogAppender::ptr appender){
        m_appender.insert(appender);
    }
    void Logger::eraseAppender(LogAppender::ptr appender){
        if(m_appender.find(appender) != m_appender.end()){
            m_appender.erase(appender);
        }
    }
}