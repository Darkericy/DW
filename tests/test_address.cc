#include "../DW/DW.h"

DW::Logger::ptr g_logger = DW::DW_LOG_ROOT();

void test() {
    std::vector<DW::Address::ptr> addrs;

    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("begin"));
    // bool v = DW::Address::Lookup(addrs, "localhost:3080");
    bool v = DW::Address::Lookup(addrs, "www.baidu.com", AF_INET);
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("end"));
    if(!v) {
        DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("lookup fail"));
        return;
    }

    for(size_t i = 0; i < addrs.size(); ++i) {
        DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING(i, " - ", addrs[i]->toString()));
    }

    auto addr = DW::Address::LookupAny("localhost:4080");
    if(addr) {
        DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, addr->toString());
    } else {
        DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, "error");
    }
}

void test_iface() {
    std::multimap<std::string, std::pair<DW::Address::ptr, uint32_t> > results;

    bool v = DW::Address::GetInterfaceAddresses(results);
    if(!v) {
        DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("GetInterfaceAddresses fail"));
        return;
    }

    for(auto& i: results) {
        DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING(i.first, " - ", i.second.first->toString(), " - ",
                                                                    i.second.second));
    }
}

void test_ipv4() {
    //auto addr = DW::IPAddress::Create("www.DW.top");
    auto addr = DW::IPAddress::Create("180.101.50.242");
    if(addr) {
        DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING(addr->toString()));
    }
}

int main(int argc, char** argv) {
    test_ipv4();
    //test_iface();
    //test();
    return 0;
}
