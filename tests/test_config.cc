#include "../DW/config.h"
#include "../DW/log.h"
#include <yaml-cpp/yaml.h>

DW::ConfigVar<int>::ptr g_int_value_config =
    DW::Config::Lookup("system.port", (int)8080, "system port");

// DW::ConfigVar<float>::ptr g_int_valuex_config =
//     DW::Config::Lookup("system.port", (float)8080, "system port");

DW::ConfigVar<float>::ptr g_float_value_config =
    DW::Config::Lookup("system.value", (float)10.2f, "system value");

DW::ConfigVar<std::vector<int> >::ptr g_int_vec_value_config =
    DW::Config::Lookup("system.int_vec", std::vector<int>{1,2}, "system int vec");

DW::ConfigVar<std::list<int> >::ptr g_int_list_value_config =
    DW::Config::Lookup("system.int_list", std::list<int>{1,2}, "system int list");

DW::ConfigVar<std::set<int> >::ptr g_int_set_value_config =
    DW::Config::Lookup("system.int_set", std::set<int>{1,2}, "system int set");

DW::ConfigVar<std::unordered_set<int> >::ptr g_int_uset_value_config =
    DW::Config::Lookup("system.int_uset", std::unordered_set<int>{1,2}, "system int uset");

DW::ConfigVar<std::map<std::string, int> >::ptr g_str_int_map_value_config =
    DW::Config::Lookup("system.str_int_map", std::map<std::string, int>{{"k",2}}, "system str int map");

DW::ConfigVar<std::unordered_map<std::string, int> >::ptr g_str_int_umap_value_config =
    DW::Config::Lookup("system.str_int_umap", std::unordered_map<std::string, int>{{"k",2}}, "system str int map");


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
    YAML::Node root = YAML::LoadFile("/home/dakericy/DK_pratice/DW/bin/config/test.yml");

    //DW::DW_LOG_DEBUG(DW::DW_LOG_ROOT(), __FILE__, __LINE__, DW::TOSTRING(root));
    print_yaml(root, 0);
}

void test_load(){
    DW::DW_LOG_DEBUG(DW::DW_LOG_ROOT(), __FILE__, __LINE__, DW::TOSTRING("before ", g_int_value_config->getValue()));
    DW::DW_LOG_DEBUG(DW::DW_LOG_ROOT(), __FILE__, __LINE__, DW::TOSTRING("before ", g_float_value_config->toString()));

#define XX(g_var, name, prefix) \
    { \
        auto& v = g_var->getValue(); \
        for(auto& i : v) { \
            DW::DW_LOG_INFO(DW::DW_LOG_ROOT(), __FILE__, __LINE__, DW::TOSTRING(#prefix, " ", #name, ": ", i));\
        } \
        DW::DW_LOG_INFO(DW::DW_LOG_ROOT(), __FILE__, __LINE__, DW::TOSTRING(#prefix, " ", #name, " yaml: ", g_var->toString()));\
    }

#define XX_M(g_var, name, prefix) \
    { \
        auto& v = g_var->getValue(); \
        for(auto& i : v) { \
            DW::DW_LOG_INFO(DW::DW_LOG_ROOT(), __FILE__, __LINE__, DW::TOSTRING(#prefix, " ", #name, ": {", \
                    i.first, " - ", i.second, "}"));\
        } \
        DW::DW_LOG_INFO(DW::DW_LOG_ROOT(), __FILE__, __LINE__, DW::TOSTRING(#prefix, " ", #name, " yaml: ", g_var->toString()));\
    }


    XX(g_int_vec_value_config, int_vec, before);
    XX(g_int_list_value_config, int_list, before);
    XX(g_int_set_value_config, int_set, before);
    XX(g_int_uset_value_config, int_uset, before);
    XX_M(g_str_int_map_value_config, str_int_map, before);
    XX_M(g_str_int_umap_value_config, str_int_umap, before);
    std::cout << std::endl;

    YAML::Node root = YAML::LoadFile("/home/dakericy/DK_pratice/DW/bin/config/test.yml");
    DW::Config::LoadFromYaml(root);

    DW::DW_LOG_INFO(DW::DW_LOG_ROOT(), __FILE__, __LINE__, DW::TOSTRING("after: ", g_int_value_config->getValue()));
    DW::DW_LOG_INFO(DW::DW_LOG_ROOT(), __FILE__, __LINE__, DW::TOSTRING("after: ", g_float_value_config->toString()));

    XX(g_int_vec_value_config, int_vec, after);
    XX(g_int_list_value_config, int_list, after);
    XX(g_int_set_value_config, int_set, after);
    XX(g_int_uset_value_config, int_uset, after);
    XX_M(g_str_int_map_value_config, str_int_map, after);
    XX_M(g_str_int_umap_value_config, str_int_umap, after);
}

void test_cb(){
    g_int_vec_value_config->addListener([](const std::vector<int>& old, const std::vector<int>& ne){
        for(const auto& o: old){
            std::cout << o << " " ;
        }
        std::cout << std::endl;

        for(const auto& n: ne){
            std::cout << n << " ";
        }
        std::cout << std::endl;
    });

    YAML::Node root = YAML::LoadFile("/home/dakericy/DK_pratice/DW/bin/config/test.yml");
    DW::Config::LoadFromYaml(root);
}

void test_log(){
    static DW::Logger::ptr system_log = DW::DW_LOG_NAME("system");
    DW::DW_LOG_INFO(system_log, __FILE__, __LINE__, DW::TOSTRING("hello system"));
    std::cout << DW::LoggerMgr::GetInstance()->toYamlString() << std::endl;
    YAML::Node root = YAML::LoadFile("/home/dakericy/DK_pratice/DW/bin/config/test.yml");
    DW::Config::LoadFromYaml(root);
    std::cout << "=============" << std::endl;
    std::cout << DW::LoggerMgr::GetInstance()->toYamlString() << std::endl;
    std::cout << "=============" << std::endl;
    std::cout << root << std::endl;
    DW::DW_LOG_INFO(system_log, __FILE__, __LINE__, DW::TOSTRING("hello system"));
    std::cout << "pause" << std::endl;
    system_log->setFormatter("%d - %m%n");
    DW::DW_LOG_INFO(system_log, __FILE__, __LINE__, DW::TOSTRING("hello system"));
    DW::DW_LOG_INFO(DW::DW_LOG_ROOT(), __FILE__, __LINE__, DW::TOSTRING("hello system"));
}

int main(){
    //test_yaml();
    //test_load();
    //test_cb();

    //test_log();

    DW::Config::Visit([](DW::ConfigVarBase::ptr var) {
        DW::DW_LOG_INFO(DW::DW_LOG_ROOT(), __FILE__, __LINE__, DW::TOSTRING(
            "name=", var->getName(),
            " description=", var->getDescription(),
            " typename=", var->getTypeName(),
            " value=", var->toString()
        ));
    });
}
