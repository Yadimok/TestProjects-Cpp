#include <iostream>
#include <string.h>
#include <asio.hpp>

using asio::ip::tcp;

int main(int argc, char *argv[])
{
    asio::io_service io_service_;
    tcp::endpoint endpoint_ {tcp::v4(), 11111};
    tcp::acceptor acceptor_(io_service_, endpoint_);
    tcp::socket socket_(io_service_);

    asio::error_code error_code_;

    acceptor_.accept(socket_);
    char data_[1024];

    asio::streambuf streambuf_;
    asio::read(socket_, streambuf_, asio::transfer_all(), error_code_);

    if (error_code_ && error_code_ != asio::error::eof) {
        std::cerr << "received failed: " << error_code_.message() << std::endl;
    } else {
        memcpy(data_, asio::buffer_cast<const char *>(streambuf_.data()), streambuf_.size());
        std::cout << "Read message from client: " << data_ << std::endl;
    }

    return 0;
}
