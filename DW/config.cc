#include "config.h"

namespace DW{
    Config::ConfigVarMap Config::s_datas;

    ConfigVarBase::ptr Config::LookupBase(const std::string& name) {
        auto it = s_datas.find(name);
        return it == s_datas.end() ? nullptr : it->second;
    }

    static void ListAllMember(const std::string& prefix,
                          const YAML::Node& node,
                          std::list<std::pair<std::string, const YAML::Node> >& output) {
        if(prefix.find_first_not_of("abcdefghikjlmnopqrstuvwxyz._012345678") != std::string::npos) {
            DW_LOG_ERROR(DW_LOG_ROOT(), __FILE__, __LINE__, TOSTRING("Config invalid name: ", prefix, " : ", node));
            return;
        }
        output.push_back(std::make_pair(prefix, node));
        if(node.IsMap()) {
            for(auto it = node.begin(); it != node.end(); ++it) {
                if(it->second.IsNull()){
                    std::cout << it->second.IsScalar();
                }
                ListAllMember(prefix.empty() ? it->first.Scalar(): prefix + "." + it->first.Scalar(), it->second, output);
            }
        }
    }

    void Config::LoadFromYaml(const YAML::Node& root) {
        std::list<std::pair<std::string, const YAML::Node> > all_nodes;
        ListAllMember("", root, all_nodes);

        for(auto& [key, cur_node] : all_nodes) {
            if(key.empty()) {
                continue;
            }

            //std::transform(key.begin(), key.end(), key.begin(), ::tolower);
            ConfigVarBase::ptr var = LookupBase(key);

            if(var) {
                if(cur_node.IsScalar()) {
                    var->fromString(cur_node.Scalar());
                } else {
                    std::ostringstream ss;
                    ss << cur_node;
                    var->fromString(ss.str());
                }
            }
        }
    }
}