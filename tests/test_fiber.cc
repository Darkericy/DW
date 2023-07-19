#include "../DW/DW.h"

DW::Logger::ptr g_logger = DW::DW_LOG_ROOT();

void run_in_fiber() {
    DW_LOG_INFO(g_logger, __FILE__, __LINE__, "run_in_fiber begin");
    DW::Fiber::YieldToHold();
    DW_LOG_INFO(g_logger, __FILE__, __LINE__, "run_in_fiber end");
    DW::Fiber::YieldToHold();
}

void test_fiber(){
    DW_LOG_INFO(g_logger, __FILE__, __LINE__, "main begin -1");
    DW::Fiber::GetThis();
    DW_LOG_INFO(g_logger, __FILE__, __LINE__, "main begin");
    DW::Fiber::ptr fiber = std::make_shared<DW::Fiber>(run_in_fiber);
    fiber->swapIn();
    DW_LOG_INFO(g_logger, __FILE__, __LINE__, "main after swapIn");
    fiber->swapIn();
    DW_LOG_INFO(g_logger, __FILE__, __LINE__, "main after end");
    fiber->swapIn();
    DW_LOG_INFO(g_logger, __FILE__, __LINE__, "main after end2");
}

int main(){
    DW::Thread::SetName("main");

    std::vector<DW::Thread::ptr> thrs;
    for(int i = 0; i < 3; ++i) {
        thrs.push_back(DW::Thread::ptr(
                    new DW::Thread(&test_fiber, "name_" + std::to_string(i))));
    }
    for(auto i : thrs) {
        i->join();
    }
    return 0;
}
