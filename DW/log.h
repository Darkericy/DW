#include <string>
#include <memory>
#include <unordered_set>

namespace DW{
    class LogEvent{
    public:
        typedef std::shared_ptr<LogEvent> ptr;

    private:
        std::string m_file;
        std::string m_content;
        uint32_t m_line;
        uint32_t m_threadID;
        uint32_t m_fiberID;
        uint64_t m_time;
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

        void log(LogLevel::Level level, LogEvent::ptr event);

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