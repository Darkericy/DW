#include <iostream>
#include <fstream>

#include "../DW/DW.h"

static DW::Logger::ptr g_logger = DW::DW_LOG_ROOT();

void test_pool() {
    DW::http::HttpConnectionPool::ptr pool(new DW::http::HttpConnectionPool(
                "www.baidu.com", "", 80, false, 10, 1000 * 30, 5));

    DW::IOManager::GetThis()->addTimer(1000, [pool](){
            auto r = pool->doGet("/", 300);
            DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING(r->toString()));
    }, true);
}

void run() {
    DW::Address::ptr addr = DW::Address::LookupAnyIPAddress("www.sylar.top:80");
    if(!addr) {
        DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("get addr error"));
        return;
    }

    DW::Socket::ptr sock = DW::Socket::CreateTCP(addr);
    bool rt = sock->connect(addr);
    if(!rt) {
        DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("connect " , *addr , " failed"));
        return;
    }

    DW::http::HttpConnection::ptr conn(new DW::http::HttpConnection(sock));
    DW::http::HttpRequest::ptr req(new DW::http::HttpRequest);
    req->setPath("/blog/");
    req->setHeader("host", "www.sylar.top");
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("req:" , "\n"
        , *req));

    conn->sendRequest(req);
    auto rsp = conn->recvResponse();

    if(!rsp) {
        DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("recv response error"));
        return;
    }
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("rsp:" , "\n"
        , *rsp));

    // std::ofstream ofs("rsp.dat");
    // ofs << *rsp;

    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, "=========================");

    auto r = DW::http::HttpConnection::DoGet("http://www.sylar.top/blog/", 300);
    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("result=" , r->result
        , " error=" , r->error
        , " rsp=" , (r->response ? r->response->toString() : "")));

    DW::DW_LOG_INFO(g_logger, __FILE__, __LINE__, DW::TOSTRING("========================="));
    test_pool();
}

// void test_https() {
//     auto r = DW::http::HttpConnection::DoGet("http://www.baidu.com/", 300, {
//                         {"Accept-Encoding", "gzip, deflate, br"},
//                         {"Connection", "keep-alive"},
//                         {"User-Agent", "curl/7.29.0"}
//             });
//     DW::DW_LOG_INFO(g_logger) , "result=" , r->result
//         , " error=" , r->error
//         , " rsp=" , (r->response ? r->response->toString() : "");

//     //DW::http::HttpConnectionPool::ptr pool(new DW::http::HttpConnectionPool(
//     //            "www.baidu.com", "", 80, false, 10, 1000 * 30, 5));
//     auto pool = DW::http::HttpConnectionPool::Create(
//                     "https://www.baidu.com", "", 10, 1000 * 30, 5);
//     DW::IOManager::GetThis()->addTimer(1000, [pool](){
//             auto r = pool->doGet("/", 3000, {
//                         {"Accept-Encoding", "gzip, deflate, br"},
//                         {"User-Agent", "curl/7.29.0"}
//                     });
//             DW::DW_LOG_INFO(g_logger) , r->toString();
//     }, true);
// }

// void test_data() {
//     DW::Address::ptr addr = DW::Address::LookupAny("www.baidu.com:80");
//     auto sock = DW::Socket::CreateTCP(addr);

//     sock->connect(addr);
//     const char buff[] = "GET / HTTP/1.1\r\n"
//                 "connection: close\r\n"
//                 "Accept-Encoding: gzip, deflate, br\r\n"
//                 "Host: www.baidu.com\r\n\r\n";
//     sock->send(buff, sizeof(buff));

//     std::string line;
//     line.resize(1024);

//     std::ofstream ofs("http.dat", std::ios::binary);
//     int total = 0;
//     int len = 0;
//     while((len = sock->recv(&line[0], line.size())) > 0) {
//         total += len;
//         ofs.write(line.c_str(), len);
//     }
//     std::cout << "total: " << total << " tellp=" << ofs.tellp() << std::endl;
//     ofs.flush();
// }

// void test_parser() {
//     std::ifstream ifs("http.dat", std::ios::binary);
//     std::string content;
//     std::string line;
//     line.resize(1024);

//     int total = 0;
//     while(!ifs.eof()) {
//         ifs.read(&line[0], line.size());
//         content.append(&line[0], ifs.gcount());
//         total += ifs.gcount();
//     }

//     std::cout , "length: " , content.size() , " total: " , total , std::endl;
//     DW::http::HttpResponseParser parser;
//     size_t nparse = parser.execute(&content[0], content.size(), false);
//     std::cout , "finish: " , parser.isFinished() , std::endl;
//     content.resize(content.size() - nparse);
//     std::cout , "rsp: " , *parser.getData() , std::endl;

//     auto& client_parser = parser.getParser();
//     std::string body;
//     int cl = 0;
//     do {
//         size_t nparse = parser.execute(&content[0], content.size(), true);
//         std::cout << "content_len: " << client_parser.content_len
//                   << " left: " << content.size()
//                   << std::endl;
//         cl += client_parser.content_len;
//         content.resize(content.size() - nparse);
//         body.append(content.c_str(), client_parser.content_len);
//         content = content.substr(client_parser.content_len + 2);
//     } while(!client_parser.chunks_done);

//     std::cout << "total: " << body.size() << " content:" << cl << std::endl;

//     DW::ZlibStream::ptr stream = DW::ZlibStream::CreateGzip(false);
//     stream->write(body.c_str(), body.size());
//     stream->flush();

//     body = stream->getResult();

//     std::ofstream ofs("http.txt");
//     ofs << body;
// }

int main(int argc, char** argv) {
    DW::IOManager iom(2);
    iom.schedule(run);
    //iom.schedule(test_https);
    return 0;
}
