#include "../DW/DW.h"

DW::Logger::ptr g_logger = DW::DW_LOG_ROOT();

void test_assert() {
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::BacktraceToString(10));
    DW_ASSERT(true, "hello util");
}

int main(){
    test_assert();
}