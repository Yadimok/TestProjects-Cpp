#include <iostream>
#include <asio.hpp>
#include <fstream>

const int SIZE_BUFFER = 1024;

int main(int argc, char *argv[])
{
	if (argc != 4) {
		std::cerr << "Usage: <ip> <port> <file>" << std::endl;
		return -1; 
	}

	try {
		std::string ip_address = argv[1];
		unsigned short port_num = atoi(argv[2]);
		std::string file = argv[3];

		std::cout << "File: " << file << std::endl;

		char buffer_[SIZE_BUFFER];
		std::error_code ec_;

		asio::ip::tcp::endpoint endpoint_(asio::ip::address::from_string(ip_address), port_num);
		asio::io_service io_service_;

		asio::ip::tcp::socket socket_(io_service_, endpoint_.protocol());
		socket_.connect(endpoint_);


		std::ifstream ifile(file.c_str(), std::ios_base::binary | std::ios_base::ate);
		if (!ifile) {
			std::cerr << "File not open." << std::endl;
			return -2;
		}

		size_t fileSize = ifile.tellg();
		ifile.seekg(0);


		asio::streambuf write_streambuf_;
		std::ostream output_(&write_streambuf_);
		output_ << file << "\n";
		output_ << fileSize << "\n\n";

		asio::write(socket_, write_streambuf_);

		std::cout << "Start sending to server..." << std::endl;

		for (;;) {
			if (!ifile.eof()) {
				ifile.read(buffer_, sizeof(buffer_));
				if (ifile.gcount() <= 0) {
					std::cerr << "Read file error." << std::endl;
					return -3;
				}

				asio::write(socket_, asio::buffer(buffer_, ifile.gcount()), asio::transfer_all(), ec_);
				if (ec_) {
					std::cerr << "Sending error." << std::endl;
				}
			} else {
				break;
			}
		}

		std::cout << "Send file " << file << std::endl;

	} catch (std::exception& exc) {
		std::cerr << "Exception message: " << exc.what() << std::endl;
	}

	return 0;

}