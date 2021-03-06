#include <boost/bind.hpp>
#include <iostream>
#include <functional>
#include <thread>
#include <vector>

#include "TCP_server.hpp"
#include "TCP_connection.hpp"


enum TCPConsts {
    max_connections = 1024,
    max_threads = 4,
};

TCP_server::TCP_server(unsigned short port)
    : port(port),
      endpoint(boost::asio::ip::tcp::v4(), port),
      // initialises an acceptor to listen on TCP port port
      acceptor(io_context, endpoint, /* reuse_addr = */ true) {}

void TCP_server::run_server() {
    acceptor.listen(max_connections);

    start_accept();

    std::cout << "Run server on " << port << " port with "
              << max_connections << " max connections and "
              << max_threads << " max threads." << std::endl;

    // running io_contexts in threads?
    std::vector<std::thread> threads;
    for (int i = 0; i < max_threads; i++)
        threads.emplace_back(std::thread(std::bind(&TCP_server::run, this)));
    for (auto &thread : threads)
        thread.join();
}

void TCP_server::handle_accept(std::shared_ptr<TCP_connection> connection,
                               const boost::system::error_code& error) {
    if (!error) {
        connection->read();
    }

    start_accept();
}

void TCP_server::start_accept() {
    std::shared_ptr<TCP_connection> connection
            (new TCP_connection(acceptor.get_executor().context()));
    acceptor.async_accept(connection->get_socket(),
                          boost::bind(&TCP_server::handle_accept,
                                      this, connection,
                                      boost::asio::placeholders::error));
}

void TCP_server::run() {
    io_context.run();
}
