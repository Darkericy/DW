#include "../DW/DW.h"

static DW::Logger::ptr g_logger = DW::DW_LOG_ROOT();

void test_fiber() {
    static int s_count = 5;
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("test in fiber s_count=", s_count));

    sleep(1);
    if(--s_count >= 0) {
        DW::Scheduler::GetThis()->schedule(&test_fiber);
    }
}

int main(int argc, char** argv) {
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, "main");
    DW::Scheduler sc(3, "test");
    sc.start();
    sleep(2);
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, "schedule");
    sc.schedule(&test_fiber);
    sc.stop();
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, "over");
    return 0;
}