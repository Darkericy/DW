#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <map>
#include <sstream>
#include <list>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
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

    template<class F, class T>
    class LexicalCast{
    public: 
        T operator ()(const F& v){
            return boost::lexical_cast<T>(v);
        }
    };

    template<class T>
    class LexicalCast<std::string, std::vector<T>>{
    public:
        typename std::vector<T> operator ()(const std::string& v){
            YAML::Node node = YAML::Load(v);
            typename std::vector<T> vec;
            std::stringstream ss;
            for(size_t i = 0; i < node.size(); ++i) {
                ss.str("");
                ss << node[i];
                vec.push_back(LexicalCast<std::string, T>()(ss.str()));
            }
            return vec;
        }
    };

    template<class T>
    class LexicalCast<std::vector<T>, std::string>{
    public:
        std::string operator ()(const std::vector<T>& v){
             YAML::Node node(YAML::NodeType::Sequence);
            for(auto& i : v) {
                node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
            }
            std::stringstream ss;
            ss << node;
            return ss.str();
        }
    };

    template<class T>
    class LexicalCast<std::string, std::list<T> > {
    public:
        std::list<T> operator()(const std::string& v) {
            YAML::Node node = YAML::Load(v);
            typename std::list<T> vec;
            std::stringstream ss;
            for(size_t i = 0; i < node.size(); ++i) {
                ss.str("");
                ss << node[i];
                vec.push_back(LexicalCast<std::string, T>()(ss.str()));
            }
            return vec;
        }
    };

    template<class T>
    class LexicalCast<std::list<T>, std::string> {
    public:
        std::string operator()(const std::list<T>& v) {
            YAML::Node node(YAML::NodeType::Sequence);
            for(auto& i : v) {
                node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
            }
            std::stringstream ss;
            ss << node;
            return ss.str();
        }
    };

    template<class T>
    class LexicalCast<std::string, std::set<T> > {
    public:
        std::set<T> operator()(const std::string& v) {
            YAML::Node node = YAML::Load(v);
            typename std::set<T> vec;
            std::stringstream ss;
            for(size_t i = 0; i < node.size(); ++i) {
                ss.str("");
                ss << node[i];
                vec.insert(LexicalCast<std::string, T>()(ss.str()));
            }
            return vec;
        }
    };

    template<class T>
    class LexicalCast<std::set<T>, std::string> {
    public:
        std::string operator()(const std::set<T>& v) {
            YAML::Node node(YAML::NodeType::Sequence);
            for(auto& i : v) {
                node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
            }
            std::stringstream ss;
            ss << node;
            return ss.str();
        }
    };

    /**
     * @brief 类型转换模板类片特化(YAML String 转换成 std::unordered_set<T>)
     */
    template<class T>
    class LexicalCast<std::string, std::unordered_set<T> > {
    public:
        std::unordered_set<T> operator()(const std::string& v) {
            YAML::Node node = YAML::Load(v);
            typename std::unordered_set<T> vec;
            std::stringstream ss;
            for(size_t i = 0; i < node.size(); ++i) {
                ss.str("");
                ss << node[i];
                vec.insert(LexicalCast<std::string, T>()(ss.str()));
            }
            return vec;
        }
    };

    /**
     * @brief 类型转换模板类片特化(std::unordered_set<T> 转换成 YAML String)
     */
    template<class T>
    class LexicalCast<std::unordered_set<T>, std::string> {
    public:
        std::string operator()(const std::unordered_set<T>& v) {
            YAML::Node node(YAML::NodeType::Sequence);
            for(auto& i : v) {
                node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
            }
            std::stringstream ss;
            ss << node;
            return ss.str();
        }
    };

    /**
     * @brief 类型转换模板类片特化(YAML String 转换成 std::map<std::string, T>)
     */
    template<class T>
    class LexicalCast<std::string, std::map<std::string, T> > {
    public:
        std::map<std::string, T> operator()(const std::string& v) {
            YAML::Node node = YAML::Load(v);
            typename std::map<std::string, T> vec;
            std::stringstream ss;
            for(auto it = node.begin();
                    it != node.end(); ++it) {
                ss.str("");
                ss << it->second;
                vec.insert(std::make_pair(it->first.Scalar(),
                            LexicalCast<std::string, T>()(ss.str())));
            }
            return vec;
        }
    };

    /**
     * @brief 类型转换模板类片特化(std::map<std::string, T> 转换成 YAML String)
     */
    template<class T>
    class LexicalCast<std::map<std::string, T>, std::string> {
    public:
        std::string operator()(const std::map<std::string, T>& v) {
            YAML::Node node(YAML::NodeType::Map);
            for(auto& i : v) {
                node[i.first] = YAML::Load(LexicalCast<T, std::string>()(i.second));
            }
            std::stringstream ss;
            ss << node;
            return ss.str();
        }
    };

    /**
     * @brief 类型转换模板类片特化(YAML String 转换成 std::unordered_map<std::string, T>)
     */
    template<class T>
    class LexicalCast<std::string, std::unordered_map<std::string, T> > {
    public:
        std::unordered_map<std::string, T> operator()(const std::string& v) {
            YAML::Node node = YAML::Load(v);
            typename std::unordered_map<std::string, T> vec;
            std::stringstream ss;
            for(auto it = node.begin();
                    it != node.end(); ++it) {
                ss.str("");
                ss << it->second;
                vec.insert(std::make_pair(it->first.Scalar(),
                            LexicalCast<std::string, T>()(ss.str())));
            }
            return vec;
        }
    };

    /**
     * @brief 类型转换模板类片特化(std::unordered_map<std::string, T> 转换成 YAML String)
     */
    template<class T>
    class LexicalCast<std::unordered_map<std::string, T>, std::string> {
    public:
        std::string operator()(const std::unordered_map<std::string, T>& v) {
            YAML::Node node(YAML::NodeType::Map);
            for(auto& i : v) {
                node[i.first] = YAML::Load(LexicalCast<T, std::string>()(i.second));
            }
            std::stringstream ss;
            ss << node;
            return ss.str();
        }
    };

    template<class T, class FromStr = LexicalCast<std::string, T>
                , class ToStr = LexicalCast<T, std::string> >
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
                //return boost::lexical_cast<std::string>(m_val);
                return ToStr()(m_val);      //这里是创建了一个匿名对象，然后调用其方法
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
                //m_val = boost::lexical_cast<T>(val);
                setValue(FromStr()(val));
            } catch (std::exception& e) {
                std::ostringstream os;
                os << "ConfigVar::fromString exception "
                    << e.what() << " convert: string to " << typeid(m_val).name();
                DW_LOG_ERROR(DW_LOG_ROOT(), __FILE__, __LINE__, os.str());
            }
            return false;
        }

        const T& getValue() {
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