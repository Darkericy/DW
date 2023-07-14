#include <iostream>
#include "../DW/log.h"
using std::cout;
using std::endl;

int main(){
    cout << "开始日志模块测试" << endl;

    DW::LoggerPtr logger = DW::DW_LOG_ROOT(); 

    cout << "构建根节点logger结束" << endl;

    DW::FileLogAppender::ptr file = std::make_shared<DW::FileLogAppender>("./bin/test.txt");
    DW::StdAppenderPtr stdt = std::make_shared<DW::StdLogAppender>();
    logger->insertAppender(file);
    logger->insertAppender(stdt);

    DW::DW_LOG_DEBUG(logger, __FILE__, __LINE__, "测试宏定义");
    DW::DW_LOG_FORMAT_DEBUG(logger, __FILE__, __LINE__, "测试宏定义%d", 6);
}