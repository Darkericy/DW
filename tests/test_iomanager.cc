#include "../DW/DW.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <sys/epoll.h>

DW::Logger::ptr g_logger = DW::DW_LOG_ROOT();

int sock = 0;

void test_fiber() {
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("test_fiber sock=", sock));

    //sleep(3);

    //close(sock);
    //sylar::IOManager::GetThis()->cancelAll(sock);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(sock, F_SETFL, O_NONBLOCK);

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    inet_pton(AF_INET, "110.242.68.66", &addr.sin_addr.s_addr);

    if(!connect(sock, (const sockaddr*)&addr, sizeof(addr))) {
    } else if(errno == EINPROGRESS) {
        DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("add event errno=", errno, " ", strerror(errno)));
        DW::IOManager::GetThis()->addEvent(sock, DW::IOManager::READ, [](){
            DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, "read callback");
        });
        DW::IOManager::GetThis()->addEvent(sock, DW::IOManager::WRITE, [](){
            DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, "write callback");
            //close(sock);
            DW::IOManager::GetThis()->cancelEvent(sock, DW::IOManager::READ);
            close(sock);
        });
    } else {
        DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("else", errno, " ", strerror(errno)));
    }

}

void test1() {
    std::cout << "EPOLLIN=" << EPOLLIN
              << " EPOLLOUT=" << EPOLLOUT << std::endl;
    DW::IOManager iom(2);
    iom.schedule(&test_fiber);
}

//DW::Timer::ptr s_timer;
void test_timer() {
    DW::IOManager iom(2);
    DW::Timer::ptr s_timer = iom.addTimer(1000, [&s_timer](){
        static int i = 0;
        DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("hello timer i=", i));
        if(++i == 3) {
            //s_timer->reset(2000, true);
            s_timer->cancel();
        }
    }, true);
}

int main(int argc, char** argv) {
    //test1();
    test_timer();
    return 0;
}