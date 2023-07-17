#include "../DW/DW.h"
#include <unistd.h>

DW::Logger::ptr g_logger = DW::DW_LOG_ROOT();

void fun1(){
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("name: ", DW::Thread::GetName(),
                                                        " this.name: ", DW::Thread::GetThis()->getName(),
                                                        " id: ", DW::GetThreadId(),
                                                        " this.id: ", DW::Thread::GetThis()->getId()));
}

void fun2(){

}

int main(){
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, "thread test begin");
    std::vector<DW::Thread::ptr> thrs;
    for(int i = 0; i < 5; ++i) {
        DW::Thread::ptr thr = std::make_shared<DW::Thread>(&fun1, DW::TOSTRING("name_", std::to_string(i)));
        thrs.push_back(thr);
    }

    for(size_t i = 0; i < thrs.size(); ++i) {
        thrs[i]->join();
    }
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, "thread test end");
}