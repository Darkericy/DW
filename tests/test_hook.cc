#include "../DW/DW.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


DW::Logger::ptr g_logger = DW::DW_LOG_ROOT();

void test_sleep() {
    DW::IOManager iom(1);
    iom.schedule([](){
        sleep(2);
        DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("sleep 2"));
    });

    iom.schedule([](){
        sleep(3);
        DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("sleep 3"));
    });
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("test sleep"));
}

void test_sock() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    inet_pton(AF_INET, "110.242.68.66", &addr.sin_addr.s_addr);


    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("begin connect"));
    int rt = connect(sock, (const sockaddr*)&addr, sizeof(addr));
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("connect rt=", rt, " errno=", errno));

    if(rt) {
        return;
    }

    const char data[] = "GET / HTTP/1.0\r\n\r\n";
    rt = send(sock, data, sizeof(data), 0);
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("send rt=", rt, " errno=", errno));

    if(rt <= 0) {
        return;
    }

    std::string buff;
    buff.resize(4096);

    rt = recv(sock, &buff[0], buff.size(), 0);
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("recv rt=", rt, " errno=", errno));

    if(rt <= 0) {
        return;
    }

    buff.resize(rt);
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING(buff));
}

int main(int argc, char** argv) {
    // test_sleep();
    DW::IOManager iom;
    iom.schedule(test_sock);
    return 0;
}