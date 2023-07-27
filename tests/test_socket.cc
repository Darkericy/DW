#include "../DW/DW.h"

static DW::Logger::ptr g_logger = DW::DW_LOG_ROOT();

void test_socket() {
    DW::IPAddress::ptr addr = DW::Address::LookupAnyIPAddress("www.baidu.com");
    if(addr) {
        DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("get address: ", addr->toString()));
    } else {
        DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("get address fail"));
        return;
    }

    DW::Socket::ptr sock = DW::Socket::CreateTCP(addr);
    addr->setPort(80);
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("addr=", addr->toString()));
    if(!sock->connect(addr)) {
        DW::DW_LOG_ERROR(g_logger, __FILE__, __LINE__, DW::TOSTRING("connect ", addr->toString(), " fail"));
        return;
    } else {
        DW::DW_LOG_ERROR(g_logger, __FILE__, __LINE__, DW::TOSTRING("connect ", addr->toString(), " connected"));
    }

    const char buff[] = "GET / HTTP/1.0\r\n\r\n";
    int rt = sock->send(buff, sizeof(buff));
    if(rt <= 0) {
        DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("send fail rt=", rt));
        return;
    }

    std::string buffs;
    buffs.resize(4096);
    rt = sock->recv(&buffs[0], buffs.size());

    if(rt <= 0) {
        DW::DW_LOG_ERROR(g_logger, __FILE__, __LINE__, DW::TOSTRING("recv fail rt=", rt));
        return;
    }

    buffs.resize(rt);
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING(buffs));
}

int main(int argc, char** argv) {
    DW::IOManager iom;
    iom.schedule(&test_socket);
    // iom.schedule(&test2);
    return 0;
}
