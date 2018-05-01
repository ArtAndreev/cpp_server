#include "TCP_server.hpp"

const unsigned short port = 8080;

int main(int argc, char** argv) {
    TCP_server server(port);
    server.run_server();

    return 0;
}
