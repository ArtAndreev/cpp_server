#include <boost/bind.hpp>
#include <iostream>

#include "TCP_connection.hpp"


TCP_connection::TCP_connection(boost::asio::io_context& io_context)
    : socket(io_context) {}

boost::asio::ip::tcp::socket& TCP_connection::get_socket() {
    return socket;
}

void TCP_connection::read() {
    /// read the request
    // example: read
    socket.async_read_some(
        boost::asio::buffer(request),
        boost::bind(&TCP_connection::handle_read,
                    shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

void TCP_connection::handle_read(const boost::system::error_code& error,
                                 size_t bytes_transferred) {
    /// send the response
    // handle the error
    if (error) return;

    // example: hello, world
    int k = snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\n");
    k += snprintf(response + k, sizeof(response) - k, "Content-Length: 13\r\n\r\n");
    k += snprintf(response + k, sizeof(response) - k, "Hello, world!");
    socket.async_write_some(
        boost::asio::buffer(response),
        [self = shared_from_this()](const boost::system::error_code& e,
                                    std::size_t bytes_transferred)->void {
            // Read again
            //self->read();
        });
}

