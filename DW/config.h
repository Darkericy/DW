#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <map>
#include <sstream>
#include <list>
#include <vector>
#include <unordered_set>
#include <set>
#include <map>
#include <functional>
#include <boost/lexical_cast.hpp>
#include <yaml-cpp/yaml.h>

#include "log.h"
#include "mutex.h"

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
        virtual std::string getTypeName() const = 0;

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
        using on_change_cb = std::function<void (const T& old_value, const T& new_value)>;
        using ptr = std::shared_ptr<ConfigVar>;
        using RWMutexType = RWMutex;

        ConfigVar(const std::string& name, 
                const T& default_value,
                const std::string& description = "")
            :ConfigVarBase(name, description)
            ,m_val(default_value) {
        }

        std::string toString() override {
            try {
                //return boost::lexical_cast<std::string>(m_val);
                RWMutexType::ReadLock lock(m_mutex);
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
            RWMutexType::ReadLock lock(m_mutex);
            return m_val;
        }

        void setValue(const T& v) {
            {
                RWMutexType::ReadLock lock(m_mutex);
                if(v == m_val){
                    return;
                }
                for(const auto& [key, cb]: m_cbs){
                    cb(m_val, v);
                }
            }

            RWMutexType::WriteLock lock(m_mutex);
            m_val = v;
        }

        std::string getTypeName() const override { return typeid(T).name();}

        uint64_t addListener(on_change_cb cb) {
            static uint64_t s_fun_id = 0;
            RWMutexType::WriteLock lock(m_mutex);
            ++s_fun_id;
            m_cbs[s_fun_id] = cb;
            return s_fun_id;
        }

        void delListener(uint64_t key) {
            RWMutexType::WriteLock lock(m_mutex);
            m_cbs.erase(key);
        }

        on_change_cb getListener(uint64_t key) {
            RWMutexType::ReadLock lock(m_mutex);
            auto it = m_cbs.find(key);
            return it == m_cbs.end() ? nullptr : it->second;
        }

        void clearListener() {
            RWMutexType::WriteLock lock(m_mutex);
            m_cbs.clear();
        }

    private:
        T m_val;
        std::unordered_map<uint64_t, on_change_cb> m_cbs;

        RWMutexType m_mutex;
    };

    class Config{
    public:
        using ConfigVarMap = std::unordered_map<std::string, ConfigVarBase::ptr>;
        using RWMutexType = RWMutex;

        template<class T>
        static typename ConfigVar<T>::ptr Lookup(const std::string& name, const T& val,
                                                const std::string& description = "")
        {
            RWMutexType::WriteLock lock(GetMutex());
            auto it = GetDatas().find(name);
            if(it != GetDatas().end()) {
                auto tmp = std::dynamic_pointer_cast<ConfigVar<T>>(it->second);
                if(tmp) {
                    DW_LOG_INFO(DW_LOG_ROOT(), __FILE__, __LINE__, TOSTRING("Lookup name=", name, " exists"));
                    return tmp;
                } else {
                    DW_LOG_INFO(DW_LOG_ROOT(), __FILE__, __LINE__, TOSTRING("Lookup name=", name, " exists but type not ",
                            typeid(T).name(), " real_type=", it->second->getTypeName(),
                            " ", it->second->toString()));
                    return nullptr;
                }
            }

            if(name.find_first_not_of("abcdefghikjlmnopqrstuvwxyz._012345678")
                    != std::string::npos) {
                std::ostringstream os;
                os << "Lookup name invalid " << name;
                DW_LOG_INFO(DW_LOG_ROOT(), __FILE__, __LINE__, os.str());
                throw std::invalid_argument(name);
            }

            typename ConfigVar<T>::ptr v(new ConfigVar<T>(name, val, description));
            GetDatas().insert({name, v});
            return v;
        }
        
        template<class T>
        static typename ConfigVar<T>::ptr Lookup(const std::string& name){
            RWMutexType::ReadLock lock(GetMutex());
            auto ret = GetDatas().find(name);
            if(ret == GetDatas().end()){
                return nullptr;
            }
            return std::dynamic_pointer_cast<ConfigVar<T>>(ret->second);
        }

        static void LoadFromYaml(const YAML::Node& root);
        static ConfigVarBase::ptr LookupBase(const std::string& name);
        static void Visit(std::function<void(ConfigVarBase::ptr)> cb);
        static void LoadFromConfDir(const std::string& path, bool force = false);
    private:

        static ConfigVarMap& GetDatas() {
            static ConfigVarMap s_datas;
            return s_datas;
        }

        static RWMutexType& GetMutex() {
            static RWMutexType s_mutex;
            return s_mutex;
        }

    };

}