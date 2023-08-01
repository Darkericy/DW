#include "../DW/DW.h"

static DW::Logger::ptr g_logger = DW::DW_LOG_ROOT();

class EchoServer : public DW::TcpServer {
public:
    EchoServer(int type);
    void handleClient(DW::Socket::ptr client);

private:
    int m_type = 0;
};

EchoServer::EchoServer(int type)
    :m_type(type) {
}

void EchoServer::handleClient(DW::Socket::ptr client) {
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("handleClient " , *client));   
    DW::ByteArray::ptr ba(new DW::ByteArray);
    while(true) {
        ba->clear();
        std::vector<iovec> iovs;
        ba->getWriteBuffers(iovs, 1024);

        int rt = client->recv(&iovs[0], iovs.size());
        if(rt == 0) {
            DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("client close: " , *client));
            break;
        } else if(rt < 0) {
            DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("client error rt=" , rt
                , " errno=" , errno , " errstr=" , strerror(errno)));
            break;
        }
        ba->setPosition(ba->getPosition() + rt);
        ba->setPosition(0);
        //DW_LOG_INFO(g_logger) << "recv rt=" << rt << " data=" << std::string((char*)iovs[0].iov_base, rt);
        if(m_type == 1) {//text 
            std::cout << ba->toString();// << std::endl;
        } else {
            std::cout << ba->toHexString();// << std::endl;
        }
        std::cout.flush();
    }
}

int type = 1;

void run() {
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("server type=" , type));
    EchoServer::ptr es(new EchoServer(type));
    auto addr = DW::Address::LookupAny("0.0.0.0:2403");
    while(!es->bind(addr)) {
        sleep(2);
    }
    es->start();
}

int main(int argc, char** argv) {
    if(argc < 2) {
        DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("used as[" , argv[0] , " -t] or [" , argv[0] , " -b]"));
        return 0;
    }

    if(!strcmp(argv[1], "-b")) {
        type = 2;
    }

    DW::IOManager iom(2);
    iom.schedule(run);
    return 0;
}
