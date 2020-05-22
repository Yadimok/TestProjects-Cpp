#include <iostream>
#include <asio.hpp>
#include <string>
#include <fstream>

const int SIZE_BUFFER = 1024;

int main(int argc, char *argv[])
{
	if (argc != 3) {
		std::cerr << "Usage: <port> <path for save>" << std::endl;
		return -1;
	}

	try {

		char buffer_[SIZE_BUFFER];

		unsigned short port_num = atoi(argv[1]);
		std::error_code ec_;

		asio::io_service io_service_;
		asio::ip::tcp::acceptor acceptor_(io_service_, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port_num));
		asio::ip::tcp::socket socket_(io_service_);
		acceptor_.accept(socket_);

		std::cout << "Client connected..." << std::endl;

		asio::streambuf read_streambuf_;

		asio::read_until(socket_, read_streambuf_, "\n\n");

		std::istream request_stream(&read_streambuf_);
		std::string path_ = argv[2], filename_;
		int size_;

		request_stream >> filename_;
		request_stream >> size_;
		request_stream.read(buffer_, 2);

		std::cout << "Received file: " << filename_ << ", size file: " << size_ << std::endl;	

		size_t pos = filename_.find_last_of('\\');
        if (pos!=std::string::npos)
            filename_ = filename_.substr(pos+1);

        path_ += "/" + filename_;

        std::cout << "Path: " << path_ << std::endl;

        std::ofstream output_file(path_.c_str(), std::ios_base::binary);

        if (!output_file)
        {
        	std::cout << "Failed to open " << path_ << std::endl;
        	return -2;
        }

        do
        {
            request_stream.read(buffer_, sizeof(buffer_));
            output_file.write(buffer_, request_stream.gcount());
        } while (request_stream.gcount()>0);

        for (;;)
        {
			size_t len = socket_.read_some(asio::buffer(buffer_), ec_);
            if (len>0)
                output_file.write(buffer_,len);
            if (output_file.tellp() == size_)
                break;
            if (ec_)
            {
                std::cout << ec_ << std::endl;
                break;
            }
        }

        std::cout << "Received " << output_file.tellp() << " bytes.\n";	

	} catch (std::exception& exc) {
		std::cerr << "Exception message: " << exc.what() << std::endl;
	}

	return 0;
}