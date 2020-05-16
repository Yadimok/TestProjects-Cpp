#include <iostream>
#include <asio.hpp>

using asio::ip::tcp;

int main(int argc, char *argv[])
{
    asio::io_service io_service_;
    asio::error_code error_code_;
    tcp::socket socket_(io_service_);
    socket_.connect(tcp::endpoint(asio::ip::address::from_string("127.0.0.1"), 11111));

    const char message_[] = "Test from client!";
    asio::write(socket_, asio::buffer(message_), error_code_);

    if (error_code_) {
        std::cerr << "Sent failed: " << error_code_.message() << std::endl;
        return -1;
    }
    std::cout << "Message is sent." << std::endl;

    return 0;
}
