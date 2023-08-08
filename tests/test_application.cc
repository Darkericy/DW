#include "../DW/application.h"

int main(int argc, char** argv) {
    DW::Application app;
    if(app.init(argc, argv)) {
        return app.run();
    }
    return 0;
}
