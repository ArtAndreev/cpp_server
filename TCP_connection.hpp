#ifndef CPP_SERVER_CLIENT_HPP
#define CPP_SERVER_CLIENT_HPP

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string>


/// Represents client connection
class TCP_connection : public boost::enable_shared_from_this<TCP_connection> {
 public:
    TCP_connection(boost::asio::io_context& io);

    boost::asio::ip::tcp::socket& get_socket();
    /// Read the data from the client
    void read();

 private:
    boost::asio::ip::tcp::socket socket; // socket for connection
    std::string request;
    std::string response;

    /// Send the data to the client
    void handle_read(const boost::system::error_code& error,
                     size_t bytes_transferred);
};

#endif //CPP_SERVER_CLIENT_HPP
