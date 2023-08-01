#include "../DW/http/http.h"
#include "../DW/log.h"

void test_request() {
    DW::http::HttpRequest::ptr req(new DW::http::HttpRequest);
    req->setHeader("host" , "www.baidu.com");
    req->setBody("hello baidu");
    req->dump(std::cout) << std::endl;
}

void test_response() {
    DW::http::HttpResponse::ptr rsp(new DW::http::HttpResponse);
    rsp->setHeader("X-X", "DW");
    rsp->setBody("hello DW");
    rsp->setStatus((DW::http::HttpStatus)400);
    rsp->setClose(false);

    rsp->dump(std::cout) << std::endl;
}

int main(int argc, char** argv) {
    test_request();
    test_response();
    return 0;
}