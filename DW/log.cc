#include "log.h"
#include "config.h"

namespace DW{
    LogEvent::LogEvent(): m_file("filename"), m_content("content"), m_threadname("threadname"),
                        m_line(0), m_threadID(0), m_fiberID(0), m_time(time(0)), m_elapse(0){

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
            MutexType::Lock lock(m_mutex);
            //std::cout << "Logger::log" << std::endl;

            for(const auto& app: m_appender){
                //std::cout << m_appender.size() << std::endl;
                app->log(self, level, event);
            }
        }
    }

    std::string Logger::toYamlString() {
        YAML::Node node;
        MutexType::Lock lock(m_mutex);
        node["name"] = m_logname;
        if(m_level != LogLevel::UNKNOW) {
            node["level"] = LogLevel::ToString(m_level);
        }

        for(auto& i : m_appender) {
            node["appenders"].push_back(YAML::Load(i->toYamlString()));
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
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
        MutexType::Lock lock(m_mutex);
        m_appender.insert(appender);
    }
    void Logger::eraseAppender(LogAppender::ptr appender){
        MutexType::Lock lock(m_mutex);
        if(m_appender.find(appender) != m_appender.end()){
            m_appender.erase(appender);
        }
    }

    void Logger::setFormatter(const std::string& pattern){
        LogFormatter::ptr new_val = std::make_shared<LogFormatter>(pattern);
        if(new_val->isError()){
            std::cout << "Logger setFormatter name=" << m_logname
                  << " pattern=" << pattern << " invalid formatter"
                  << std::endl;
            return;
        }
        setFormatter(new_val);
    }

    void Logger::setFormatter(LogFormatter::ptr pattern){
        MutexType::Lock lock(m_mutex);
        for(auto& appender: m_appender){
            //MutexType::Lock ll(appender->m_mutex);
            //和大佬的不太一样，我在这里没有加锁(真的可以吗？)
            appender->setFormatter(pattern);
        }
    }

    void LogAppender::setFormatter(LogFormatter::ptr formatter){
        MutexType::Lock lock(m_mutex);
        m_formatter = formatter;
    }
    LogFormatter::ptr LogAppender::getFormatter(){
        MutexType::Lock lock(m_mutex);
        return m_formatter;
    }

    void StdLogAppender::log(LoggerPtr logger, LogLevel::Level level, LogEvent::ptr event){
        if(level >= m_level){
            //std::cout << "StdLogAppender::log" << std::endl;
            MutexType::Lock lock(m_mutex);
            std::cout << m_formatter->formatter(logger, level, event);
        }
    }

    std::string StdLogAppender::toYamlString() {
        YAML::Node node;
        MutexType::Lock lock(m_mutex);
        node["type"] = "StdoutLogAppender";
        if(m_level != LogLevel::UNKNOW) {
            node["level"] = LogLevel::ToString(m_level);
        }
        if(m_formatter) {
            node["formatter"] = m_formatter->getPattern();
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }

    void FileLogAppender::log(LoggerPtr logger, LogLevel::Level level, LogEvent::ptr event){
        if(level >= m_level){
            //std::cout << "FileLogAppender::log" << std::endl;
            uint64_t now = event->getTime();
            //std::cout << now - m_lastTime << std::endl;
            if(now >= (m_lastTime + 3)) {
                reopen();
                m_lastTime = now;
            }

            MutexType::Lock lock(m_mutex);
            m_filestream << m_formatter->formatter(logger, level, event);
        }
    }

    bool FileLogAppender::reopen(){
        MutexType::Lock lock(m_mutex);
        if(m_filestream.is_open()){
            //std::cout << "here" << std::endl;
            m_filestream.close();
        }
        m_filestream.open(m_filename, std::ios::app);
        return !!m_filestream;      //不得不说这里两个否定符号是真的让我感叹，这个大佬在各个细节上真的很让我很佩服
    }

    std::string FileLogAppender::toYamlString() {
        YAML::Node node;
        MutexType::Lock lock(m_mutex);
        node["type"] = "FileLogAppender";
        node["file"] = m_filename;
        if(m_level != LogLevel::UNKNOW) {
            node["level"] = LogLevel::ToString(m_level);
        }
        if(m_formatter) {
            node["formatter"] = m_formatter->getPattern();
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
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
        XX(ENABLE)
    #undef XX
        default:
            return "UNKNOW";
        }
        return "UNKNOW";
    }

    LogLevel::Level LogLevel::FromString(const std::string& str) {
    #define XX(level, v) \
        if(str == #v) { \
            return LogLevel::level; \
        }
        XX(DEBUG, debug);
        XX(INFO, info);
        XX(WARN, warn);
        XX(ERROR, error);
        XX(FATAL, fatal);
        XX(ENABLE, enable);

        XX(DEBUG, DEBUG);
        XX(INFO, INFO);
        XX(WARN, WARN);
        XX(ERROR, ERROR);
        XX(FATAL, FATAL);
        XX(ENABLE, ENABLE);
        return LogLevel::UNKNOW;
    #undef XX
    }

    LogFormatter::LogFormatter(): m_pattern("%d{%Y-%m-%d %H:%M:%S}%T%t%T%N%T%F%T[%p]%T[%c]%T%f:%l%T%m%n"),
                                m_items(){
                                    init();
                                }

    LogFormatter::LogFormatter(const std::string& pattern): 
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

    LoggerManager::LoggerManager(): m_root(std::make_shared<Logger>("root")){
        //std::cout << 1;
        m_root->insertAppender(std::make_shared<StdLogAppender>());
        m_root->setLevel(LogLevel::INFO);
        m_loggers["root"] = m_root;
    }

    void LoggerManager::insertLogger(Logger::ptr logger){
        MutexType::Lock lock(m_mutex);
        m_loggers.insert({logger->getName(), logger});
    }

    Logger::ptr LoggerManager::getLogger(const std::string& name){
        {
            MutexType::Lock lock(m_mutex);
            auto it = m_loggers.find(name);
            if(it != m_loggers.end()){
                return it->second;
            }
        }

        Logger::ptr tmp = std::make_shared<Logger>(name);
        tmp->setAppenderList(m_root->getAppenderList());
        tmp->setLevel(m_root->getLevel());
        LoggerMgr::GetInstance()->insertLogger(tmp);
        return tmp;
    }

    Logger::ptr LoggerManager::getRoot(){
        return m_root;
    }

    std::string LoggerManager::toYamlString() {
        YAML::Node node;
        MutexType::Lock lock(m_mutex);
        for(auto& i : m_loggers) {
            node.push_back(YAML::Load(i.second->toYamlString()));
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }

    struct LogAppenderDefine{
        int type = 0; //1 File, 2 Stdout
        LogLevel::Level level = LogLevel::UNKNOW;
        std::string formatter;
        std::string file;

        bool operator==(const LogAppenderDefine& oth) const {
            return type == oth.type
                && level == oth.level
                && formatter == oth.formatter
                && file == oth.file;
        }
    };

    struct LogDefine{
        std::string name;
        LogLevel::Level level = LogLevel::UNKNOW;
        std::vector<LogAppenderDefine> appenders;

        bool operator==(const LogDefine& oth) const {
            return name == oth.name
                && level == oth.level
                && appenders == appenders;
        }

        bool operator<(const LogDefine& oth) const {
            return name < oth.name;
        }

        bool isValid() const {
            return !name.empty();
        }
    };

    template<>
    class LexicalCast<std::string, LogDefine> {
    public:
        LogDefine operator()(const std::string& v) {
            YAML::Node n = YAML::Load(v);
            LogDefine ld;
            if(!n["name"].IsDefined()) {
                std::cout << "log config error: name is null, " << n << std::endl;
                throw std::logic_error("log config name is null");
            }
            ld.name = n["name"].as<std::string>();
            ld.level = LogLevel::FromString(n["level"].IsDefined() ? n["level"].as<std::string>() : "");

            if(n["appenders"].IsDefined()) {
                //std::cout << "==" << ld.name << " = " << n["appenders"].size() << std::endl;
                for(size_t x = 0; x < n["appenders"].size(); ++x) {
                    auto a = n["appenders"][x];
                    if(!a["type"].IsDefined()) {
                        std::cout << "log config error: appender type is null, " << a
                                << std::endl;
                        continue;
                    }
                    std::string type = a["type"].as<std::string>();
                    LogAppenderDefine lad;
                    if(type == "FileLogAppender") {
                        lad.type = 1;
                        if(!a["file"].IsDefined()) {
                            std::cout << "log config error: fileappender file is null, " << a
                                << std::endl;
                            continue;
                        }
                        lad.file = a["file"].as<std::string>();
                        if(a["formatter"].IsDefined()) {
                            lad.formatter = a["formatter"].as<std::string>();
                        }
                    } else if(type == "StdoutLogAppender") {
                        lad.type = 2;
                        if(a["formatter"].IsDefined()) {
                            lad.formatter = a["formatter"].as<std::string>();
                        }
                    } else {
                        std::cout << "log config error: appender type is invalid, " << a
                                << std::endl;
                        continue;
                    }

                    ld.appenders.push_back(lad);
                }
            }
            return ld;
        }
    };

    template<>
    class LexicalCast<LogDefine, std::string> {
    public:
        std::string operator()(const LogDefine& i) {
            YAML::Node n;
            n["name"] = i.name; //和map一样，直接用中括号就会创建这个组建。
            if(i.level != LogLevel::UNKNOW) {
                n["level"] = LogLevel::ToString(i.level);
            }

            for(auto& a : i.appenders) {
                YAML::Node na;
                if(a.type == 1) {
                    na["type"] = "FileLogAppender";
                    na["file"] = a.file;
                } else if(a.type == 2) {
                    na["type"] = "StdoutLogAppender";
                }
                if(a.level != LogLevel::UNKNOW) {
                    na["level"] = LogLevel::ToString(a.level);
                }

                if(!a.formatter.empty()) {
                    na["formatter"] = a.formatter;
                }

                n["appenders"].push_back(na);   //还能嵌套节点
            }
            std::stringstream ss;
            ss << n;
            return ss.str();
        }
    };

    //初始化一个yml文件的入口
    ConfigVar<std::set<LogDefine>>::ptr g_log_defines =
        Config::Lookup("logs", std::set<LogDefine>(), "logs config");

    struct LogIniter{
        LogIniter(){
            g_log_defines->addListener([](const std::set<LogDefine>& old_value,
                    const std::set<LogDefine>& new_value){
                DW_LOG_INFO(DW_LOG_ROOT(), __FILE__, __LINE__, "on_logger_conf_changed");
                for(auto& i : new_value) {
                    auto it = old_value.find(i);
                    Logger::ptr logger;
                    if(it == old_value.end()) {
                        //新增logger
                        logger = DW_LOG_NAME(i.name);
                    } else {
                        if(!(i == *it)) {
                            //修改的logger
                            logger = DW_LOG_NAME(i.name);
                        } else {
                            continue;
                        }
                    }

                    logger->setLevel(i.level);

                    logger->clearAppenders();
                    for(auto& a : i.appenders) {
                        LogAppender::ptr ap;
                        if(a.type == 1) {
                            ap.reset(new FileLogAppender(a.file));
                        } else if(a.type == 2) {
                            ap.reset(new StdLogAppender);
                        }
                        ap->setLevel(a.level);
                        if(!a.formatter.empty()) {
                            LogFormatter::ptr fmt(new LogFormatter(a.formatter));
                            if(!fmt->isError()) {
                                ap->setFormatter(fmt);
                            } else {
                                std::cout << "log.name=" << i.name << " appender type=" << a.type
                                        << " formatter=" << a.formatter << " is invalid" << std::endl;
                            }
                        }
                        logger->insertAppender(ap);
                        //把新弄好的logger放入manager中
                        LoggerMgr::GetInstance()->insertLogger(logger);
                    }
                }

                for(auto& i : old_value) {
                    auto it = new_value.find(i);
                    if(it == new_value.end()) {
                        //删除logger
                        //并不是严格意义上的删除
                        auto logger = DW_LOG_NAME(i.name);
                        logger->setLevel(LogLevel::ENABLE);
                        logger->clearAppenders();
                    }
                }
            });
        }
    };

    static LogIniter __log_init;
}