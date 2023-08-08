#include "../DW/DW.h"
#include <unistd.h>
#include <iostream>
#include <fstream>

struct A {
    A() {
        std::ifstream ifs("/proc/" + std::to_string(getpid()) + "/cmdline", std::ios::binary);
        std::string content;
        content.resize(4096);

        ifs.read(&content[0], content.size());
        content.resize(ifs.gcount());

        for(size_t i = 0; i < content.size(); ++i) {
            std::cout << i << " - " << content[i] << " - " << (int)content[i] << std::endl;
        }
    }
};

A a;

int main(int argc, char** argv) {
    std::cout << "argc=" << argc << std::endl;
    DW::EnvMgr::GetInstance()->addHelp("s", "start with the terminal");
    DW::EnvMgr::GetInstance()->addHelp("d", "run as daemon");
    DW::EnvMgr::GetInstance()->addHelp("p", "print help");
    if(!DW::EnvMgr::GetInstance()->init(argc, argv)) {
        DW::EnvMgr::GetInstance()->printHelp();
        return 0;
    }

    std::cout << "exe=" << DW::EnvMgr::GetInstance()->getExe() << std::endl;
    std::cout << "cwd=" << DW::EnvMgr::GetInstance()->getCwd() << std::endl;

    std::cout << "path=" << DW::EnvMgr::GetInstance()->getEnv("PATH", "xxx") << std::endl;
    std::cout << "test=" << DW::EnvMgr::GetInstance()->getEnv("TEST", "") << std::endl;
    std::cout << "set env " << DW::EnvMgr::GetInstance()->setEnv("TEST", "yy") << std::endl;
    std::cout << "test=" << DW::EnvMgr::GetInstance()->getEnv("TEST", "") << std::endl;
    if(DW::EnvMgr::GetInstance()->has("p")) {
        DW::EnvMgr::GetInstance()->printHelp();
    }
    return 0;
}
