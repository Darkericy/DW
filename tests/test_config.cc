#include "../DW/config.h"
#include "../DW/log.h"
#include <yaml-cpp/yaml.h>

DW::ConfigVar<int>::ptr g_int_value_config =
    DW::Config::Lookup("system.port", (int)8080, "system port");

DW::ConfigVar<float>::ptr g_float_value_config =
    DW::Config::Lookup("system.value", (float)10.2f, "system value");

void print_yaml(const YAML::Node& node, int level) {
    if(node.IsScalar()) {
        DW::DW_LOG_INFO(DW::DW_LOG_ROOT(), __FILE__, __LINE__, DW::TOSTRING(std::string(level * 4, ' '),
                        node.Scalar(), " - ", node.Type(), " - ", level));
    } else if(node.IsNull()) {
        DW::DW_LOG_INFO(DW::DW_LOG_ROOT(), __FILE__, __LINE__, DW::TOSTRING(std::string(level * 4, ' '),
                        "NULL - ", node.Type(), " - ", level));
    } else if(node.IsMap()) {
        for(auto it = node.begin();
                it != node.end(); ++it) {
            DW::DW_LOG_INFO(DW::DW_LOG_ROOT(), __FILE__, __LINE__, DW::TOSTRING(std::string(level * 4, ' '),
                            it->first, " - ", it->second.Type(), " - ", level));
            print_yaml(it->second, level + 1);
        }
    } else if(node.IsSequence()) {
        for(size_t i = 0; i < node.size(); ++i) {
            DW::DW_LOG_INFO(DW::DW_LOG_ROOT(), __FILE__, __LINE__, DW::TOSTRING(std::string(level * 4, ' '),
                            i, " - ", node[i].Type(), " - ", level));
            print_yaml(node[i], level + 1);
        }
    }
}

void test_yaml(){
    YAML::Node root = YAML::LoadFile("/home/dakericy/DK_pratice/DW/bin/config/log.yml");

    //DW::DW_LOG_DEBUG(DW::DW_LOG_ROOT(), __FILE__, __LINE__, DW::TOSTRING(root));
    print_yaml(root, 0);
}

void test_load(){
    DW::DW_LOG_DEBUG(DW::DW_LOG_ROOT(), __FILE__, __LINE__, DW::TOSTRING("before ", g_int_value_config->getValue()));
    DW::DW_LOG_DEBUG(DW::DW_LOG_ROOT(), __FILE__, __LINE__, DW::TOSTRING("before ", g_float_value_config->toString()));

    YAML::Node root = YAML::LoadFile("/home/dakericy/DK_pratice/DW/bin/config/log.yml");
    DW::Config::LoadFromYaml(root);

    DW::DW_LOG_DEBUG(DW::DW_LOG_ROOT(), __FILE__, __LINE__, DW::TOSTRING("after ", g_int_value_config->getValue()));
    DW::DW_LOG_DEBUG(DW::DW_LOG_ROOT(), __FILE__, __LINE__, DW::TOSTRING("after ", g_float_value_config->toString()));
}

int main(){
    //test_yaml();

    test_load();
}
