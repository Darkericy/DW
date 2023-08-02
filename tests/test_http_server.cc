#include "../DW/http/http_server.h"
#include "../DW/log.h"

static DW::Logger::ptr g_logger = DW::DW_LOG_ROOT();

#define XX(...) #__VA_ARGS__


DW::IOManager::ptr worker;
void run() {
    g_logger->setLevel(DW::LogLevel::INFO);
    DW::http::HttpServer::ptr server(new DW::http::HttpServer(true, worker.get(), DW::IOManager::GetThis()));
    // DW::http::HttpServer::ptr server(new DW::http::HttpServer(false));
    DW::Address::ptr addr = DW::Address::LookupAnyIPAddress("0.0.0.0:2403");
    while(!server->bind(addr)) {
        sleep(2);
    }
    auto sd = server->getServletDispatch();
    sd->addServlet("/DW/xx", [](DW::http::HttpRequest::ptr req
                ,DW::http::HttpResponse::ptr rsp
                ,DW::http::HttpSession::ptr session) {
            rsp->setBody(req->toString());
            return 0;
    });

    sd->addGlobServlet("/DW/*", [](DW::http::HttpRequest::ptr req
                ,DW::http::HttpResponse::ptr rsp
                ,DW::http::HttpSession::ptr session) {
            rsp->setBody("Glob:\r\n" + req->toString());
            return 0;
    });

    sd->addGlobServlet("/DWx/*", [](DW::http::HttpRequest::ptr req
                ,DW::http::HttpResponse::ptr rsp
                ,DW::http::HttpSession::ptr session) {
            rsp->setBody(XX(<html>
<head><title>404 Not Found</title></head>
<body>
<center><h1>404 Not Found</h1></center>
<hr><center>nginx/1.16.0</center>
</body>
</html>
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
));
            return 0;
    });

    server->start();
}

int main(int argc, char** argv) {
    DW::IOManager iom(2, "main");
    worker.reset(new DW::IOManager(3, "worker"));
    iom.schedule(run);
    return 0;
}
