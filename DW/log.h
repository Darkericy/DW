#include <string>
#include <memory>
#include <unordered_set>

namespace DW{
    class LogEvent{
    public:
        typedef std::shared_ptr<LogEvent> ptr;

    private:
        std::string m_file;     //文件名
        std::string m_content;  //日志信息
        uint32_t m_line;        //行号
        uint32_t m_threadID;    //线程号
        uint32_t m_fiberID;     //携程号
        uint64_t m_time;        //时间戳
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
    };

    class LogFormatter{
    public:
        typedef std::shared_ptr<LogFormatter> ptr;

        std::string formatter(LogLevel::Level level, LogEvent::ptr event);
    };

    class LogAppender{
    public:
        typedef std::shared_ptr<LogAppender> ptr;

        virtual ~LogAppender();
        void log(LogLevel::Level level, LogEvent::ptr event);
    };

    class Logger{
    public: 
        typedef std::shared_ptr<Logger> ptr;

        void debug(LogLevel::Level level, LogEvent::ptr event);
        void info(LogLevel::Level level, LogEvent::ptr event);
        void warn(LogLevel::Level level, LogEvent::ptr event);
        void error(LogLevel::Level level, LogEvent::ptr event);
        void fatal(LogLevel::Level level, LogEvent::ptr event);

        void log(LogLevel::Level level, LogEvent::ptr event);

        //设置和返回等级
        LogLevel::Level getLevel();
        void setLevel(LogLevel::Level level);

        //插入和删除输出地
        void insertAppender(LogAppender::ptr appender);
        void eraseAppender(LogAppender::ptr appender);

    private:    
        std::string m_logname;                          
        LogLevel::Level m_level;
        std::unordered_set<LogAppender::ptr> m_appender;
    };

    class StdLogAppender: public LogAppender{

    };

    class FileLogAppender: public LogAppender{

    };
}