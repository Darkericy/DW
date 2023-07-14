#pragma once

#include <string>
#include <memory>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <map>
#include <functional>

namespace DW{
    class Logger;
    class LogEvent;
    class LogAppender;
    class LogFormatter;
    class StdLogAppender;
    class FileLogAppender;

    using LoggerPtr = std::shared_ptr<Logger>;
    using EventPtr = std::shared_ptr<LogEvent>;
    using AppenderPtr = std::shared_ptr<LogAppender>;
    using FormatterPtr = std::shared_ptr<LogFormatter>;
    using StdAppenderPtr = std::shared_ptr<StdLogAppender>;
    using FileAppenderPtr = std::shared_ptr<FileLogAppender>;

    class LogEvent{
    public:
        using ptr = std::shared_ptr<LogEvent> ;

        LogEvent();
        LogEvent(const std::string& file, const std::string& content, const std::string& threadname,
                uint32_t line, uint32_t threadID, uint32_t fiberID, uint32_t time, uint32_t elapse);

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
            DEBUG = 1,
            INFO = 2,
            WARN = 3,
            ERROR = 4,
            FATAL = 5
        };

        static std::string ToString(Level level);
    };

    class LogFormatter{
    public:
        using ptr = std::shared_ptr<LogFormatter>;

        LogFormatter(const std::string& pattern);

        std::string formatter(LoggerPtr logger, LogLevel::Level level, LogEvent::ptr event);

        void init();

        void setPattern(const std::string& pattern){ m_pattern = pattern; };
        std::string getPattern(){ return m_pattern; };

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

        std::string getName() { return m_logname; };

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
    };

    class FileLogAppender: public LogAppender{
    public: 
        using ptr = std::shared_ptr<FileLogAppender>;
        
        FileLogAppender(const std::string& filename): LogAppender(), m_filename(filename), m_filestream(filename){
            
        }

        void log(LoggerPtr logger, LogLevel::Level level, LogEvent::ptr event) override;

        bool reopen();

    private:    
        std::string m_filename;
        std::ofstream m_filestream;
    };
};