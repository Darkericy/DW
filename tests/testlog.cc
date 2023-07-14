#include <iostream>
#include "../DW/log.cc"
using std::cout;
using std::endl;

int main(){
    std::fstream os("text.txt");

    cout << "开始日志模块测试" << endl;

    DW::LoggerPtr logger = std::make_shared<DW::Logger>("test");

    cout << "构建根节点logger结束" << endl;

    DW::FileLogAppender::ptr file = std::make_shared<DW::FileLogAppender>("./bin/test.txt");
    DW::StdAppenderPtr stdt = std::make_shared<DW::StdLogAppender>();
    logger->insertAppender(file);
    logger->insertAppender(stdt);

    file->setLevel(DW::LogLevel::ERROR);

    cout << "插入需要的输出器结束" << endl;

    DW::EventPtr event = std::make_shared<DW::LogEvent>();

    cout << "创建基本事件" << endl;

    logger->log(DW::LogLevel::DEBUG, event);

    cout << "日志测试完毕" << endl;
}