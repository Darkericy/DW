#include "../DW/DW.h"
#include <unistd.h>

DW::Logger::ptr g_logger = DW::DW_LOG_ROOT();

long long count = 0;
//DW::RWMutex s_mutex;
DW::Mutex s_mutex;

void fun1(){
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("name: ", DW::Thread::GetName(),
                                                        " this.name: ", DW::Thread::GetThis()->getName(),
                                                        " id: ", DW::GetThreadId(),
                                                        " this.id: ", DW::Thread::GetThis()->getId()));
    
    for(int i = 0; i < 100000; ++i) {
        DW::Mutex::Lock lock(s_mutex);
        ++count;
    }
}

void fun2(){
    while(1){
        DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    }
}

void fun3(){
    while(1){
        DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, "=======================================");
    }
}

int main(){
    //std::cout << "thread test begin" << std::endl;
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, "thread test begin");

    YAML::Node root = YAML::LoadFile("/home/dakericy/DK_pratice/DW/bin/config/log.yml");
    DW::Config::LoadFromYaml(root);

    std::vector<DW::Thread::ptr> thrs;
    for(int i = 0; i < 8; ++i) {
        DW::Thread::ptr thr = std::make_shared<DW::Thread>(&fun2, DW::TOSTRING("name_", std::to_string(i * 2)));
        DW::Thread::ptr thr2 = std::make_shared<DW::Thread>(&fun3, DW::TOSTRING("name_", std::to_string(i * 2 + 1)));
        thrs.push_back(thr);
        thrs.push_back(thr2);
    }

    for(size_t i = 0; i < thrs.size(); ++i) {
        thrs[i]->join();
    }
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, "thread test end");
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("count ", count));
}