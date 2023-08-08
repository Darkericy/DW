#include "../DW/daemon.h"
#include "../DW/iomanager.h"
#include "../DW/log.h"

static DW::Logger::ptr g_logger = DW::DW_LOG_ROOT();

DW::Timer::ptr timer;
int server_main(int argc, char** argv) {
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING(DW::ProcessInfoMgr::GetInstance()->toString()));
    DW::IOManager iom(1);
    timer = iom.addTimer(1000, [](){
            DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("onTimer"));
            // static int count = 0;
            // if(++count > 10) {
            //     exit(1);
            // }
    }, true);
    return 0;
}

int main(int argc, char** argv) {
    // std::cout <<
    return DW::start_daemon(argc, argv, server_main, argc != 1);
}
