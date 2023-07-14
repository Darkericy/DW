#include "log.h"

namespace DW{
    LogEvent::LogEvent(): m_file("filename"), m_content("content"), m_threadname("threadname"),
                        m_line(0), m_threadID(0), m_fiberID(0), m_time(1), m_elapse(0){

    };
    LogEvent::LogEvent(const std::string& file, const std::string& content, const std::string& threadname,
            uint32_t line, uint32_t threadID, uint32_t fiberID, uint32_t time, uint32_t elapse):
            m_file(file), m_content(content), m_threadname(threadname),
            m_line(line), m_threadID(threadID), m_fiberID(fiberID), m_time(time), m_elapse(elapse){

            }

    class StringFormatItem : public LogFormatter::FormatterItem {
    public:
        StringFormatItem(const std::string& str)
            :m_string(str) {}
        void format(std::ostream& os, LoggerPtr logger, LogLevel::Level level, LogEvent::ptr event) override {
            os << m_string;
        }
    private:
        std::string m_string;
    };
    class MessageFormatItem: public LogFormatter::FormatterItem{
    public:
        MessageFormatItem(const std::string& = "") {};

        void format(std::ostream& os, LoggerPtr logger, LogLevel::Level level, LogEvent::ptr event) override{
            os << event->getContent();
        };
    };
    class LevelFormatItem: public LogFormatter::FormatterItem{
    public:        
        LevelFormatItem(const std::string& = "") {};

        void format(std::ostream& os, LoggerPtr logger, LogLevel::Level level, LogEvent::ptr event) override{
            os << LogLevel::ToString(level);
        };
    };
    class ElapseFormatItem: public LogFormatter::FormatterItem{
    public:
        ElapseFormatItem(const std::string& = "") {};

        void format(std::ostream& os, LoggerPtr logger, LogLevel::Level level, LogEvent::ptr event) override{
            os << event->getElapse();
        };
    };
    class NameFormatItem: public LogFormatter::FormatterItem{
    public:
        NameFormatItem(const std::string& = "") {};

        void format(std::ostream& os, LoggerPtr logger, LogLevel::Level level, LogEvent::ptr event) override{
            os << logger->getName();
        };
    };
    class ThreadIdFormatItem: public LogFormatter::FormatterItem{
    public:
        ThreadIdFormatItem(const std::string& = "") {};

        void format(std::ostream& os, LoggerPtr logger, LogLevel::Level level, LogEvent::ptr event) override{
            os << event->getThreadID();
        };
    };
    class NewLineFormatItem: public LogFormatter::FormatterItem{
    public:
        NewLineFormatItem(const std::string& = "") {};

        void format(std::ostream& os, LoggerPtr logger, LogLevel::Level level, LogEvent::ptr event) override{
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
        void format(std::ostream& os, LoggerPtr logger, LogLevel::Level level, LogEvent::ptr event) override{
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
        FilenameFormatItem(const std::string& = "") {};

        void format(std::ostream& os, LoggerPtr logger, LogLevel::Level level, LogEvent::ptr event) override{
            os << event->getFile();
        };
    };
    class LineFormatItem: public LogFormatter::FormatterItem{
    public:
        LineFormatItem(const std::string& = "") {};

        void format(std::ostream& os, LoggerPtr logger, LogLevel::Level level, LogEvent::ptr event) override{
            os << event->getLine();
        };
    };
    class TabFormatItem: public LogFormatter::FormatterItem{
    public:
        TabFormatItem(const std::string& = "") {};

        void format(std::ostream& os, LoggerPtr logger, LogLevel::Level level, LogEvent::ptr event) override{
            os << "\t";
        };
    };
    class FiberIdFormatItem: public LogFormatter::FormatterItem{
    public:
        FiberIdFormatItem(const std::string& = "") {};

        void format(std::ostream& os, LoggerPtr logger, LogLevel::Level level, LogEvent::ptr event) override{
            os << event->getFiberID();
        };
    };
    class ThreadNameFormatItem: public LogFormatter::FormatterItem{
    public:
        ThreadNameFormatItem(const std::string& = "") {};

        void format(std::ostream& os, LoggerPtr logger, LogLevel::Level level, LogEvent::ptr event) override{
            os << event->getThreadName();
        };
    };

    Logger::Logger(const std::string& name): m_logname(name), m_level(LogLevel::DEBUG){

    }

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
            //std::cout << "获取自己的智能指针之前" << std::endl;

            auto self = shared_from_this();

            //std::cout << "Logger::log" << std::endl;

            for(const auto& app: m_appender){
                //std::cout << "Logger::log in for" << std::endl;
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

    void StdLogAppender::log(LoggerPtr logger, LogLevel::Level level, LogEvent::ptr event){
        if(level >= m_level){
            //std::cout << "StdLogAppender::log" << std::endl;
            std::cout << m_formatter->formatter(logger, level, event);
        }
    }

    void FileLogAppender::log(LoggerPtr logger, LogLevel::Level level, LogEvent::ptr event){
        if(level >= m_level){
            //std::cout << "FileLogAppender::log" << std::endl;
            m_filestream << m_formatter->formatter(logger, level, event);
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

    LogFormatter::LogFormatter(const std::string& pattern = "%d{%Y-%m-%d %H:%M:%S}%T%t%T%N%T%F%T[%p]%T[%c]%T%f:%l%T%m%n"): 
    m_pattern(pattern), m_items(){
        //std::cout << m_pattern << std::endl;
        init();
        //std::cout << m_items.size() << std::endl;
    }

    std::string LogFormatter::formatter(LoggerPtr logger, LogLevel::Level level, LogEvent::ptr event){
        std::stringstream ss;

        //std::cout << m_pattern << std::endl;
        for(auto& item: m_items){
            //std::cout << "LogFormatter::formatter in for" << std::endl;
            item->format(ss, logger, level, event);
        }

        return ss.str();
    }

    //解析日志输出格式。
    //%xxx %xxx{xxx} %%
    void LogFormatter::init(){
        //str, format, type
    std::vector<std::tuple<std::string, std::string, int> > vec;
    std::string nstr;   //保存不是格式的部分
    for(size_t i = 0; i < m_pattern.size(); ++i) {
        //检索百分号
        if(m_pattern[i] != '%') {
            nstr.append(1, m_pattern[i]);
            continue;
        }

        if((i + 1) < m_pattern.size()) {
            if(m_pattern[i + 1] == '%') {
                nstr.append(1, '%');
                continue;
            }
        }

        size_t n = i + 1;       //从i + 1的地方开始
        int fmt_status = 0;     //记录当前解析的状态（是否在解析大括号内容）
        size_t fmt_begin = 0;   //记录大括号的解析位置

        std::string str;
        std::string fmt;
        while(n < m_pattern.size()) {
            if(!fmt_status && (!isalpha(m_pattern[n]) && m_pattern[n] != '{'
                    && m_pattern[n] != '}')) {
                str = m_pattern.substr(i + 1, n - i - 1);
                break;
            }
            if(fmt_status == 0) {
                if(m_pattern[n] == '{') {
                    str = m_pattern.substr(i + 1, n - i - 1);
                    //std::cout << "*" << str << std::endl;
                    fmt_status = 1; //解析格式
                    fmt_begin = n;
                    ++n;
                    continue;
                }
            } else if(fmt_status == 1) {
                if(m_pattern[n] == '}') {
                    fmt = m_pattern.substr(fmt_begin + 1, n - fmt_begin - 1);
                    //std::cout << "#" << fmt << std::endl;
                    fmt_status = 0;
                    ++n;
                    break;
                }
            }
            ++n;
            if(n == m_pattern.size()) {
                if(str.empty()) {
                    str = m_pattern.substr(i + 1);
                }
            }
        }

        if(fmt_status == 0) {
            if(!nstr.empty()) {
                vec.push_back(std::make_tuple(nstr, std::string(), 0));
                nstr.clear();
            }
            vec.push_back(std::make_tuple(str, fmt, 1));
            i = n - 1;
        } else if(fmt_status == 1) {
            std::cout << "pattern parse error: " << m_pattern << " - " << m_pattern.substr(i) << std::endl;
            m_error = true;
            vec.push_back(std::make_tuple("<<pattern_error>>", fmt, 0));
        }
    }

    if(!nstr.empty()) {
        vec.push_back(std::make_tuple(nstr, "", 0));
    }
    static std::map<std::string, std::function<FormatterItem::ptr(const std::string& str)>> s_format_items = {
#define XX(str, C) \
        {#str, [](const std::string& fmt) { return FormatterItem::ptr(new C(fmt));}}

        XX(m, MessageFormatItem),           //m:消息
        XX(p, LevelFormatItem),             //p:日志级别
        XX(r, ElapseFormatItem),            //r:累计毫秒数
        XX(c, NameFormatItem),              //c:日志名称
        XX(t, ThreadIdFormatItem),          //t:线程id
        XX(n, NewLineFormatItem),           //n:换行
        XX(d, DateTimeFormatItem),          //d:时间
        XX(f, FilenameFormatItem),          //f:文件名
        XX(l, LineFormatItem),              //l:行号
        XX(T, TabFormatItem),               //T:Tab
        XX(F, FiberIdFormatItem),           //F:协程id
        XX(N, ThreadNameFormatItem),        //N:线程名称
#undef XX
    };

    for(auto& i : vec) {
        if(std::get<2>(i) == 0) {
            m_items.push_back(FormatterItem::ptr(new StringFormatItem(std::get<0>(i))));
            // m_items.push_back(std::make_shared(StringFormatItem(std::get<0>(i))));
        } else {
            auto it = s_format_items.find(std::get<0>(i));  //获取到迭代器
            if(it == s_format_items.end()) {
                m_items.push_back(FormatterItem::ptr(new StringFormatItem("<<error_format %" + std::get<0>(i) + ">>")));
                m_error = true;
            } else {
                m_items.push_back(it->second(std::get<1>(i)));  //调用其构造函数，构造用的字符串是fmt
            }
        }

        //std::cout << "(" << std::get<0>(i) << ") - (" << std::get<1>(i) << ") - (" << std::get<2>(i) << ")" << std::endl;
    }
    //std::cout << m_items.size() << std::endl;
    }
}