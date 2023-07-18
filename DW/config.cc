#include "config.h"

namespace DW{
    ConfigVarBase::ptr Config::LookupBase(const std::string& name) {
        RWMutexType::ReadLock lock(GetMutex());
        auto it = GetDatas().find(name);
        return it == GetDatas().end() ? nullptr : it->second;
    }

    static void ListAllMember(const std::string& prefix,
                          const YAML::Node& node,
                          std::list<std::pair<std::string, const YAML::Node> >& output) 
    {
        if(prefix.find_first_not_of("abcdefghikjlmnopqrstuvwxyz._012345678") != std::string::npos) {
            DW_LOG_ERROR(DW_LOG_ROOT(), __FILE__, __LINE__, TOSTRING("Config invalid name: ", prefix, " : ", node));
            return;
        }
        output.push_back(std::make_pair(prefix, node));
        if(node.IsMap()) {
            for(auto it = node.begin(); it != node.end(); ++it) {
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
                    //DW_LOG_DEBUG(DW_LOG_ROOT(), __FILE__, __LINE__, TOSTRING(key, " ", cur_node.Scalar()));
                    var->fromString(cur_node.Scalar());
                } else {
                    std::ostringstream ss;
                    ss << cur_node;
                    var->fromString(ss.str());
                }
            }
        }
    }

    void Config::Visit(std::function<void(ConfigVarBase::ptr)> cb) {
        RWMutexType::ReadLock lock(GetMutex());
        ConfigVarMap& m = GetDatas();
        for(auto it = m.begin();
                it != m.end(); ++it) {
            cb(it->second);
        }

    }
}