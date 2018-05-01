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
    // example: echo
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
    if (error == boost::asio::error::eof)
    {
        std::cout << "Disconnected client with IP: "
                  << socket.remote_endpoint().address().to_string()
                  << std::endl;
    }
    if (error) return;

    // example: echo
    response = request;
    socket.async_write_some(
        boost::asio::buffer(response),
        boost::bind(&TCP_connection::handle_read, shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
//    read();
}

