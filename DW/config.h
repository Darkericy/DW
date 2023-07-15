#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <map>
#include <sstream>
#include <list>
#include <boost/lexical_cast.hpp>
#include <yaml-cpp/yaml.h>

#include "log.h"

namespace DW{
    class ConfigVarBase{
    public:
        using ptr = std::shared_ptr<ConfigVarBase>;

        ConfigVarBase(const std::string& name, const std::string& description = "")
            :m_name(name)
            ,m_description(description) {
            std::transform(m_name.begin(), m_name.end(), m_name.begin(), ::tolower);
        }

        std::string getName(){
            return m_name;
        }
        std::string getDescription(){
            return m_description;
        }

        virtual std::string toString() = 0;
        virtual bool fromString(const std::string& val) = 0;

    protected:
        std::string m_name;
        std::string m_description;
    };

    template<class T>
    class ConfigVar: public ConfigVarBase{
    public:

        using ptr = std::shared_ptr<ConfigVar>;

        ConfigVar(const std::string& name, 
                const T& default_value,
                const std::string& description = "")
            :ConfigVarBase(name, description)
            ,m_val(default_value) {
        }

        std::string toString() override {
            try {
                return boost::lexical_cast<std::string>(m_val);
            } catch (std::exception& e) {
                std::ostringstream os;
                os << "ConfigVar::toString exception "
                << e.what() <<  " convert: " << typeid(m_val).name() << " to string";
                DW_LOG_ERROR(DW_LOG_ROOT(), __FILE__, __LINE__, os.str());
            }
            return "";
        }

        bool fromString(const std::string& val) override {
            try {
                m_val = boost::lexical_cast<T>(val);
            } catch (std::exception& e) {
                std::ostringstream os;
                os << "ConfigVar::fromString exception "
                    << e.what() << " convert: string to " << typeid(m_val).name();
                DW_LOG_ERROR(DW_LOG_ROOT(), __FILE__, __LINE__, os.str());
            }
            return false;
        }

        const T getValue() {
            return m_val;
        }

        void setValue(const T& v) {
            m_val = v;
        }

    private:
        T m_val;
    };

    class Config{
    public:
        using ConfigVarMap = std::unordered_map<std::string, ConfigVarBase::ptr>;

        template<class T>
        static typename ConfigVar<T>::ptr Lookup(const std::string& name, const T& val,
                                                const std::string& description = "")
        {
            auto it = Lookup<T>(name);
            if(it) {
                std::ostringstream os;
                os << "Lookup name=" << name << " exists";
                DW_LOG_INFO(DW_LOG_ROOT(), __FILE__, __LINE__, os.str());
                return it;
            }

            if(name.find_first_not_of("abcdefghikjlmnopqrstuvwxyz._012345678")
                    != std::string::npos) {
                std::ostringstream os;
                os << "Lookup name invalid " << name;
                DW_LOG_INFO(DW_LOG_ROOT(), __FILE__, __LINE__, os.str());
                throw std::invalid_argument(name);
            }

            typename ConfigVar<T>::ptr v(new ConfigVar<T>(name, val, description));
            s_datas.insert({name, v});
            return v;
        }
        
        template<class T>
        static typename ConfigVar<T>::ptr Lookup(const std::string& name){
            auto ret = s_datas.find(name);
            if(ret == s_datas.end()){
                return nullptr;
            }
            return std::dynamic_pointer_cast<ConfigVar<T>>(ret->second);
        }

        static void LoadFromYaml(const YAML::Node& root);


    private:
        static ConfigVarMap s_datas;

        static ConfigVarBase::ptr LookupBase(const std::string& name);
    };
}