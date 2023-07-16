#pragma once

#include <string>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <map>
#include <functional>
#include <stdarg.h>

#include "util.h"
#include "singleton.h"

namespace DW{
    class Logger;
    class LogEvent;
    class LogAppender;
    class LogFormatter;
    class StdLogAppender;
    class FileLogAppender;
    class LoggerManager;

    using LoggerPtr = std::shared_ptr<Logger>;
    using EventPtr = std::shared_ptr<LogEvent>;
    using AppenderPtr = std::shared_ptr<LogAppender>;
    using FormatterPtr = std::shared_ptr<LogFormatter>;
    using StdAppenderPtr = std::shared_ptr<StdLogAppender>;
    using FileAppenderPtr = std::shared_ptr<FileLogAppender>;

    using LoggerMgr = SingletonPtr<LoggerManager>;

    class LogEvent{
    public:
        using ptr = std::shared_ptr<LogEvent> ;

        LogEvent();
        LogEvent(const std::string& file, const std::string& content, const std::string& threadname,
                uint32_t line, uint32_t threadID, uint32_t fiberID, uint32_t time, uint32_t elapse);
        ~LogEvent() = default;

        std::string getFile() { return m_file; };
        std::string getContent() { return m_content; };
        std::string getThreadName() { return m_threadname; };
        uint32_t getLine() {return m_line; };
        uint32_t getThreadID() { return m_threadID; };
        uint32_t getFiberID() { return m_fiberID; };
        uint64_t getTime() { return m_time; };
        uint64_t getElapse() { return m_elapse; };

        void setFile(const std::string& file) { m_file = file; };
        void setContent(const std::string& content) { m_content = content; };
        void setThreadName(const std::string& threadname) { m_threadname = threadname; };
        void setLine(const uint32_t line) { m_line = line; };
        void setThreadID(const uint32_t threadID) { m_threadID = threadID; };
        void setFiberID(const uint32_t fiberID) { m_fiberID = fiberID; };
        void setTime(const uint64_t time) { m_time = time; };
        void setElpase(const uint64_t elpase) { m_elapse = elpase; };

        void contentFormat(const char* format, ...){
            char* buf = nullptr;
            va_list vaList;
            va_start(vaList, format);
            int len = vasprintf(&buf, format, vaList);
            if(len != -1){
                m_content = buf;
                free(buf);
            }
            va_end(vaList);
        }

    private:
        std::string m_file;         //文件名
        std::string m_content;      //日志信息
        std::string m_threadname;   //线程名
        uint32_t m_line;            //行号
        uint32_t m_threadID;        //线程号
        uint32_t m_fiberID;         //携程号
        uint64_t m_time;            //时间戳
        uint64_t m_elapse;          //累计毫秒
    };

    class LogLevel{
    public: 
        enum Level{
            UNKNOW = 0,
            DEBUG = 1,
            INFO = 2,
            WARN = 3,
            ERROR = 4,
            FATAL = 5,
            ENABLE = 6
        };

        static std::string ToString(Level level);
        static LogLevel::Level FromString(const std::string& str);
    };

    class LogFormatter{
    public:
        using ptr = std::shared_ptr<LogFormatter>;

        LogFormatter();
        LogFormatter(const std::string& pattern);

        std::string formatter(LoggerPtr logger, LogLevel::Level level, LogEvent::ptr event);

        void init();

        void setPattern(const std::string& pattern){ 
            m_pattern = pattern;    
            clearItems();
            init();
        };
        std::string getPattern(){ return m_pattern; };

        bool isError(){
            return m_error;
        }

        class FormatterItem{
        public: 
            typedef std::shared_ptr<FormatterItem> ptr;
            
            virtual ~FormatterItem() {};

            virtual void format(std::ostream& os, LoggerPtr logger, LogLevel::Level level, LogEvent::ptr event) = 0;
        };

    private:
        std::string m_pattern;
        std::vector<FormatterItem::ptr> m_items;

        bool m_error = false;   //检查格式是否有错

        void clearItems(){
            m_items.clear();
        }
    };

    class LogAppender{
    public:
        using ptr = std::shared_ptr<LogAppender>;

        LogAppender():m_level(LogLevel::DEBUG), m_formatter(std::make_shared<LogFormatter>()) {
            //std::cout << "LogAppender creater" << std::endl;
        };

        virtual ~LogAppender() {};
        virtual void log(LoggerPtr logger, LogLevel::Level level, LogEvent::ptr event) = 0;

        void setFormatter(LogFormatter::ptr formatter){ m_formatter = formatter; };
        LogFormatter::ptr getFormatter() { return m_formatter; };

        void setLevel(LogLevel::Level level){ m_level = level; };
        LogLevel::Level getLevel(){ return m_level; };

        virtual std::string toYamlString() = 0;

    protected:
        LogLevel::Level m_level;
        LogFormatter::ptr m_formatter;
    };

    class Logger: public std::enable_shared_from_this<Logger>{
    public: 
        using ptr =  std::shared_ptr<Logger>;

        Logger(const std::string& name);

        void debug(LogEvent::ptr event);
        void info(LogEvent::ptr event);
        void warn(LogEvent::ptr event);
        void error(LogEvent::ptr event);
        void fatal(LogEvent::ptr event);

        void log(LogLevel::Level level, LogEvent::ptr event);

        //设置和返回等级
        LogLevel::Level getLevel();
        void setLevel(LogLevel::Level level);

        //插入和删除输出地
        void insertAppender(LogAppender::ptr appender);
        void eraseAppender(LogAppender::ptr appender);
        void clearAppenders(){
            m_appender.clear();
        }
        std::unordered_set<LogAppender::ptr> getAppenderList(){
            return m_appender;
        }
        void setAppenderList(const std::unordered_set<LogAppender::ptr>& list){
            m_appender = list;
        }
        void setFormatter(const std::string& pattern);

        std::string getName() { return m_logname; };

        std::string toYamlString();

    private:    
        std::string m_logname;                          
        LogLevel::Level m_level;
        std::unordered_set<LogAppender::ptr> m_appender;
    };

    class StdLogAppender: public LogAppender{
    public: 
        using ptr = std::shared_ptr<StdLogAppender>;

        StdLogAppender(): LogAppender(){};
        
        void log(LoggerPtr logger, LogLevel::Level level, LogEvent::ptr event) override;

        std::string toYamlString() override;
    };

    class FileLogAppender: public LogAppender{
    public: 
        using ptr = std::shared_ptr<FileLogAppender>;
        
        FileLogAppender(const std::string& filename): LogAppender(), m_filename(filename), m_filestream(filename){
            
        }

        void log(LoggerPtr logger, LogLevel::Level level, LogEvent::ptr event) override;

        std::string toYamlString() override;

        bool reopen();

    private:    
        std::string m_filename;
        std::ofstream m_filestream;
    };

    class LoggerManager{
    public:
    
        LoggerManager();

        void insertLogger(Logger::ptr logger);
        Logger::ptr getLogger(const std::string& name);
        Logger::ptr getRoot();

        std::string toYamlString();

    private:
        Logger::ptr m_root;
        std::unordered_map<std::string, Logger::ptr> m_loggers;
    };

    //成功，在不用宏的前提下成果实现了视频中的功能。
    inline void DW_LOG_LEVEL(Logger::ptr logger, std::string file, uint32_t line, 
                            std::string content, LogLevel::Level level){
        if(level >= logger->getLevel()){
            LogEvent::ptr event = std::make_shared<LogEvent>();
            event->setThreadID(GetThreadId());
            event->setFiberID(GetFiberId());
            event->setFile(file);
            event->setLine(line);
            event->setContent(content);

            logger->log(level, event);
        }
    }

    inline void DW_LOG_DEBUG(Logger::ptr logger, std::string file, uint32_t line, std::string content){
        DW_LOG_LEVEL(logger, file, line, content, LogLevel::DEBUG);
    }
    inline void DW_LOG_INFO(Logger::ptr logger, std::string file, uint32_t line, std::string content){
        DW_LOG_LEVEL(logger, file, line, content, LogLevel::INFO);
    }
    inline void DW_LOG_WARN(Logger::ptr logger, std::string file, uint32_t line, std::string content){
        DW_LOG_LEVEL(logger, file, line, content, LogLevel::WARN);
    }
    inline void DW_LOG_ERROR(Logger::ptr logger, std::string file, uint32_t line, std::string content){
        DW_LOG_LEVEL(logger, file, line, content, LogLevel::ERROR);
    }
    inline void DW_LOG_FATAL(Logger::ptr logger, std::string file, uint32_t line, std::string content){
        DW_LOG_LEVEL(logger, file, line, content, LogLevel::FATAL);
    }

    template <typename... Args>
    inline void DW_LOG_FORMAT_LEVEL(Logger::ptr logger, std::string file, uint32_t line, LogLevel::Level level, 
                                    const char* format, Args&&... args){
        if(level >= logger->getLevel()){
            LogEvent::ptr event = std::make_shared<LogEvent>();
            event->setThreadID(GetThreadId());
            event->setFiberID(GetFiberId());
            event->setFile(file);
            event->setLine(line);
            event->contentFormat(format, std::forward<Args>(args)...);

            logger->log(level, event);
        }
    }

    template <typename... Args>
    inline void DW_LOG_FORMAT_DEBUG(Logger::ptr logger, std::string file, uint32_t line, 
                                    const char* format, Args&&... args){
        DW_LOG_FORMAT_LEVEL(logger, file, line, LogLevel::DEBUG, format, std::forward<Args>(args)...);
    }
    template <typename... Args>
    inline void DW_LOG_FORMAT_INFO(Logger::ptr logger, std::string file, uint32_t line, 
                                    const char* format, Args&&... args){
        DW_LOG_FORMAT_LEVEL(logger, file, line, LogLevel::INFO, format, std::forward<Args>(args)...);
    }
    template <typename... Args>
    inline void DW_LOG_FORMAT_WARN(Logger::ptr logger, std::string file, uint32_t line, 
                                    const char* format, Args&&... args){
        DW_LOG_FORMAT_LEVEL(logger, file, line, LogLevel::INFO, format, std::forward<Args>(args)...);
    }
    template <typename... Args>
    inline void DW_LOG_FORMAT_ERROR(Logger::ptr logger, std::string file, uint32_t line, 
                                    const char* format, Args&&... args){
        DW_LOG_FORMAT_LEVEL(logger, file, line, LogLevel::INFO, format, std::forward<Args>(args)...);
    }
    template <typename... Args>
    inline void DW_LOG_FORMAT_FATAL(Logger::ptr logger, std::string file, uint32_t line, 
                                    const char* format, Args&&... args){
        DW_LOG_FORMAT_LEVEL(logger, file, line, LogLevel::INFO, format, std::forward<Args>(args)...);
    }

    inline LoggerPtr DW_LOG_ROOT(){
        return LoggerMgr::GetInstance()->getRoot();
    }
    inline LoggerPtr DW_LOG_NAME(const std::string& name){
        return LoggerMgr::GetInstance()->getLogger(name);
    }

    template<typename ... Args>
    inline std::string TOSTRING(const Args ... args){
        std::ostringstream os;
        ((os << args), ...);
        return os.str();
    }

};