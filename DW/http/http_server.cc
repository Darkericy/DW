#include "http_server.h"
#include "../log.h"
#include "servlet.h"

namespace DW {
namespace http {

static DW::Logger::ptr g_logger = DW_LOG_NAME("system");

HttpServer::HttpServer(bool keepalive
               ,DW::IOManager* worker
               ,DW::IOManager* io_worker
               ,DW::IOManager* accept_worker)
    :TcpServer(worker, io_worker, accept_worker)
    ,m_isKeepalive(keepalive) {
    m_dispatch.reset(new ServletDispatch);

    m_type = "http";
    // m_dispatch->addServlet("/_/status", Servlet::ptr(new StatusServlet));
    // m_dispatch->addServlet("/_/config", Servlet::ptr(new ConfigServlet));
}

void HttpServer::setName(const std::string& v) {
    TcpServer::setName(v);
    m_dispatch->setDefault(std::make_shared<NotFoundServlet>(v));
}

void HttpServer::handleClient(Socket::ptr client) {
    DW_LOG_DEBUG(g_logger, __FILE__, __LINE__, TOSTRING("handleClient " , *client));
    HttpSession::ptr session(new HttpSession(client));
    do {
        auto req = session->recvRequest();
        if(!req) {
            DW_LOG_DEBUG(g_logger, __FILE__, __LINE__, TOSTRING("recv http request fail, errno="
                , errno , " errstr=" , strerror(errno)
                , " cliet:" , *client , " keep_alive=" , m_isKeepalive));
            break;
        }

        HttpResponse::ptr rsp(new HttpResponse(req->getVersion()
                            ,req->isClose() || !m_isKeepalive));
        rsp->setHeader("Server", getName());
        m_dispatch->handle(req, rsp, session);
        session->sendResponse(rsp);

        if(!m_isKeepalive || req->isClose()) {
            break;
        }
    } while(true);
    session->close();
}

}
}
