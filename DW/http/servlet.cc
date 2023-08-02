#include "servlet.h"
#include <fnmatch.h>

namespace DW {
namespace http {

FunctionServlet::FunctionServlet(callback cb)
    :Servlet("FunctionServlet")
    ,m_cb(cb) {
}

int32_t FunctionServlet::handle(DW::http::HttpRequest::ptr request
               , DW::http::HttpResponse::ptr response
               , DW::http::HttpSession::ptr session) {
    return m_cb(request, response, session);
}



ServletDispatch::ServletDispatch()
    :Servlet("ServletDispatch") {
    m_default.reset(new NotFoundServlet("DW/1.0"));
}

int32_t ServletDispatch::handle(DW::http::HttpRequest::ptr request
               , DW::http::HttpResponse::ptr response
               , DW::http::HttpSession::ptr session) {
    auto slt = getMatchedServlet(request->getPath());
    if(slt) {
        slt->handle(request, response, session);
    }
    return 0;
}

void ServletDispatch::addServlet(const std::string& uri, Servlet::ptr slt) {
    RWMutexType::WriteLock lock(m_mutex);
    m_datas[uri] = slt;
}

// void ServletDispatch::addServletCreator(const std::string& uri, IServletCreator::ptr creator) {
//     RWMutexType::WriteLock lock(m_mutex);
//     m_datas[uri] = creator;
// }

// void ServletDispatch::addGlobServletCreator(const std::string& uri, IServletCreator::ptr creator) {
//     RWMutexType::WriteLock lock(m_mutex);
//     for(auto it = m_globs.begin();
//             it != m_globs.end(); ++it) {
//         if(it->first == uri) {
//             m_globs.erase(it);
//             break;
//         }
//     }
//     m_globs.push_back(std::make_pair(uri, creator));
// }

void ServletDispatch::addServlet(const std::string& uri
                        ,FunctionServlet::callback cb) {
    RWMutexType::WriteLock lock(m_mutex);
    m_datas[uri] = std::make_shared<FunctionServlet>(cb);
}

void ServletDispatch::addGlobServlet(const std::string& uri
                                    ,Servlet::ptr slt) {
    RWMutexType::WriteLock lock(m_mutex);
    //需要把旧的相同的删除
    for(auto it = m_globs.begin();
            it != m_globs.end(); ++it) {
        if(it->first == uri) {
            m_globs.erase(it);
            break;
        }
    }
    m_globs.push_back(std::make_pair(uri, (slt)));
}

void ServletDispatch::addGlobServlet(const std::string& uri
                                ,FunctionServlet::callback cb) {
    return addGlobServlet(uri, std::make_shared<FunctionServlet>(cb));
}

void ServletDispatch::delServlet(const std::string& uri) {
    RWMutexType::WriteLock lock(m_mutex);
    m_datas.erase(uri);
}

void ServletDispatch::delGlobServlet(const std::string& uri) {
    RWMutexType::WriteLock lock(m_mutex);
    for(auto it = m_globs.begin();
            it != m_globs.end(); ++it) {
        if(it->first == uri) {
            m_globs.erase(it);
            break;
        }
    }
}

Servlet::ptr ServletDispatch::getServlet(const std::string& uri) {
    RWMutexType::ReadLock lock(m_mutex);
    auto it = m_datas.find(uri);
    return it == m_datas.end() ? nullptr : it->second;
}

Servlet::ptr ServletDispatch::getGlobServlet(const std::string& uri) {
    RWMutexType::ReadLock lock(m_mutex);
    for(auto it = m_globs.begin();
            it != m_globs.end(); ++it) {
        if(it->first == uri) {
            return it->second;
        }
    }
    return nullptr;
}

Servlet::ptr ServletDispatch::getMatchedServlet(const std::string& uri) {
    RWMutexType::ReadLock lock(m_mutex);
    auto mit = m_datas.find(uri);
    if(mit != m_datas.end()) {
        return mit->second;
    }
    for(auto it = m_globs.begin();
            it != m_globs.end(); ++it) {
        if(!fnmatch(it->first.c_str(), uri.c_str(), 0)) {
            return it->second;
        }
    }
    return m_default;
}

// void ServletDispatch::listAllServletCreator(std::map<std::string, IServletCreator::ptr>& infos) {
//     RWMutexType::ReadLock lock(m_mutex);
//     for(auto& i : m_datas) {
//         infos[i.first] = i.second;
//     }
// }

// void ServletDispatch::listAllGlobServletCreator(std::map<std::string, IServletCreator::ptr>& infos) {
//     RWMutexType::ReadLock lock(m_mutex);
//     for(auto& i : m_globs) {
//         infos[i.first] = i.second;
//     }
// }

NotFoundServlet::NotFoundServlet(const std::string& name)
    :Servlet("NotFoundServlet")
    ,m_name(name) {
    m_content = "<html><head><title>404 Not Found"
        "</title></head><body><center><h1>404 Not Found</h1></center>"
        "<hr><center>" + name + "</center></body></html>";

}

int32_t NotFoundServlet::handle(DW::http::HttpRequest::ptr request
                   , DW::http::HttpResponse::ptr response
                   , DW::http::HttpSession::ptr session) {
    response->setStatus(DW::http::HttpStatus::NOT_FOUND);
    response->setHeader("Server", "DW/1.0.0");
    response->setHeader("Content-Type", "text/html");
    response->setBody(m_content);
    return 0;
}


}
}
