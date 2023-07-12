#include "log.h"

namespace DW{
    void Logger::debug(LogEvent::ptr event){
        log(LogLevel::DEBUG, event);
    }
    void Logger::info(LogEvent::ptr event){
        log(LogLevel::INFO, event);
    }
    void Logger::warn(LogEvent::ptr event){
        log(LogLevel::WARN, event);
    }
    void Logger::error(LogEvent::ptr event){
        log(LogLevel::ERROR, event);
    }
    void Logger::fatal(LogEvent::ptr event){
        log(LogLevel::FATAL, event);
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

    void StdLogAppender::log(LogLevel::Level level, LogEvent::ptr event){
        if(level > m_level){
            m_formatter->formatter(level, event);
        }
    }

    void FileLogAppender::log(LogLevel::Level level, LogEvent::ptr event){
        if(level > m_level){
            m_formatter->formatter(level, event);
        }
    }

    bool FileLogAppender::reopen(){
        if(!m_filestream){
            m_filestream.open(m_filename);
        }
        return !!m_filestream;      //不得不说这里两个否定符号是真的让我感叹，这个大佬在各个细节上真的很让我很佩服
    }
}