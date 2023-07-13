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
    class LogEvent{
    public:
        typedef std::shared_ptr<LogEvent> ptr;

        std::string getFile() { return m_file; };
        std::string getContent() { return m_content; };
        std::string getThreadName() { return m_threadname; };
        uint32_t getLine() {return m_line; };
        uint32_t getThreadID() { return m_threadID; };
        uint32_t getFiberID() { return m_fiberID; };
        uint64_t getTime() { return m_time; };
        uint64_t getElapse() { return m_elapse; };

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
        typedef std::shared_ptr<LogFormatter> ptr;

        LogFormatter(const std::string& pattern);

        std::string formatter(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event);

        void init();

        void setPattern(const std::string& pattern){ m_pattern = pattern; };
        std::string getPattern(){ return m_pattern; };

        class FormatterItem{
        public: 
            typedef std::shared_ptr<FormatterItem> ptr;
            
            virtual ~FormatterItem() {};

            virtual void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) = 0;
        };

    private:
        std::string m_pattern;
        std::vector<FormatterItem::ptr> m_items;

        bool m_error = false;   //检查格式是否有错
    };

    class LogAppender{
    public:
        typedef std::shared_ptr<LogAppender> ptr;

        virtual ~LogAppender() {};
        virtual void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) = 0;

        void setFormatter(LogFormatter::ptr formatter){ m_formatter = formatter; };
        LogFormatter::ptr getFormatter() { return m_formatter; };

    protected:
        LogLevel::Level m_level;
        LogFormatter::ptr m_formatter;
    };

    class Logger: public std::enable_shared_from_this<Logger>{
    public: 
        typedef std::shared_ptr<Logger> ptr;

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
        typedef std::shared_ptr<StdLogAppender> ptr;
        
        void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override;
    };

    class FileLogAppender: public LogAppender{
    public: 
        typedef std::shared_ptr<FileLogAppender> ptr;
        
        void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override;

        bool reopen();

    private:    
        std::string m_filename;
        std::ofstream m_filestream;
    };
};