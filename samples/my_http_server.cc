#include "../DW/DW.h"

DW::Logger::ptr g_logger = DW::DW_LOG_ROOT();
DW::IOManager::ptr worker;
void run() {
    g_logger->setLevel(DW::LogLevel::INFO);
    DW::Address::ptr addr = DW::Address::LookupAnyIPAddress("0.0.0.0:2403");
    if(!addr) {
        DW_LOG_ERROR(g_logger, __FILE__, __LINE__, "get address error");
        return;
    }

    // DW::http::HttpServer::ptr http_server(new DW::http::HttpServer(true, worker.get()));
    DW::http::HttpServer::ptr http_server(new DW::http::HttpServer(true));
    while(!http_server->bind(addr)) {
        DW_LOG_ERROR(g_logger, __FILE__, __LINE__, TOSTRING("bind " , *addr , " fail"));
        sleep(1);
    }

    http_server->start();
}

int main(int argc, char** argv) {
    DW::IOManager iom(2);
    // worker.reset(new DW::IOManager(2));
    iom.schedule(run);
    return 0;
}
