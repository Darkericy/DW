#include "log.h"

namespace DW{
    class MessageFormatItem: public LogFormatter::FormatterItem{
    public:
        void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override{
            os << event->getContent();
        };
    };
    class LevelFormatItem: public LogFormatter::FormatterItem{
    public:        
        void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override{
            os << LogLevel::ToString(level);
        };
    };
    class ElapseFormatItem: public LogFormatter::FormatterItem{
    public:
        void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override{
            os << event->getElapse();
        };
    };
    class NameFormatItem: public LogFormatter::FormatterItem{
    public:
        void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override{
            os << logger->getName();
        };
    };
    class ThreadIdFormatItem: public LogFormatter::FormatterItem{
    public:
        void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override{
            os << event->getThreadID();
        };
    };
    class NewLineFormatItem: public LogFormatter::FormatterItem{
    public:
        void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override{
            os << std::endl;
        };
    };
    class DateTimeFormatItem: public LogFormatter::FormatterItem{
    public:
        DateTimeFormatItem(std::string pattern = "%Y-%m-%d %H:%M:%S"): m_pattern(pattern){
            if(m_pattern.empty()){
                m_pattern = "%Y-%m-%d %H:%M:%S";
            }
        }

        //这部分属于我最不熟悉的部分
        void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override{
            struct tm tm;
            time_t time = event->getTime();
            localtime_r(&time, &tm);
            char buf[64];
            strftime(buf, sizeof(buf), m_pattern.c_str(), &tm);
            os << buf;
        };

    private:
        std::string m_pattern;
    };
    class FilenameFormatItem: public LogFormatter::FormatterItem{
    public:
        void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override{
            os << event->getFile();
        };
    };
    class LineFormatItem: public LogFormatter::FormatterItem{
    public:
        void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override{
            os << event->getLine();
        };
    };
    class TabFormatItem: public LogFormatter::FormatterItem{
    public:
        void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override{
            os << "\t";
        };
    };
    class FiberIdFormatItem: public LogFormatter::FormatterItem{
    public:
        void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override{
            os << event->getFiberID();
        };
    };
    class ThreadNameFormatItem: public LogFormatter::FormatterItem{
    public:
        void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override{
            os << event->getThreadName();
        };
    };

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
            auto self = shared_from_this();

            for(const auto& app: m_appender){
                app->log(self, level, event);
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

    void StdLogAppender::log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event){
        if(level > m_level){
            m_formatter->formatter(logger, level, event);
        }
    }

    void FileLogAppender::log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event){
        if(level > m_level){
            m_formatter->formatter(logger, level, event);
        }
    }

    bool FileLogAppender::reopen(){
        if(!m_filestream){
            m_filestream.open(m_filename);
        }
        return !!m_filestream;      //不得不说这里两个否定符号是真的让我感叹，这个大佬在各个细节上真的很让我很佩服
    }

    std::string LogLevel::ToString(Level level){
        switch(level){
    #define XX(name) \
        case LogLevel::name: \
            return #name; \
            break;

        XX(DEBUG);
        XX(INFO);
        XX(WARN);
        XX(ERROR);
        XX(FATAL);
    #undef XX
        default:
            return "UNKNOW";
        }
        return "UNKNOW";
    }

    LogFormatter::LogFormatter(const std::string& pattern): m_pattern(pattern){
        init();
    }

    std::string LogFormatter::formatter(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event){
        std::stringstream ss;

        for(const auto& item: m_itemlist){
            item->format(ss, logger, level, event);
        }

        return ss.str();
    }

    void LogFormatter::init(){
        
    }
}