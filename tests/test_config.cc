#include "../DW/config.h"
#include "../DW/log.h"

DW::ConfigVar<int>::ptr g_int_value_config =
    DW::Config::Lookup("system.port", (int)8080, "system port");

DW::ConfigVar<float>::ptr g_float_value_config =
    DW::Config::Lookup("system.value", (float)10.2f, "system value");

int main(){
    DW::DW_LOG_DEBUG(DW::DW_LOG_ROOT(), __FILE__, __LINE__, std::to_string(g_int_value_config->getValue()));
    DW::DW_LOG_DEBUG(DW::DW_LOG_ROOT(), __FILE__, __LINE__, g_float_value_config->toString());
}
