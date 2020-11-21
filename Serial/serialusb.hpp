#ifndef SERIALUSB_HPP
#define SERIALUSB_HPP

#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <iostream>

typedef boost::tuple<
        boost::asio::serial_port_base::character_size,
        boost::asio::serial_port_base::parity,
        boost::asio::serial_port_base::stop_bits,
        boost::asio::serial_port_base::flow_control> SerialParams;

static const SerialParams SP_8N1 = boost::make_tuple(
    8,
    boost::asio::serial_port_base::parity::none,
    boost::asio::serial_port_base::stop_bits::one,
    boost::asio::serial_port_base::flow_control::none
);

static const SerialParams SP_8O1 = boost::make_tuple(
    8,
    boost::asio::serial_port_base::parity::odd,
    boost::asio::serial_port_base::stop_bits::one,
    boost::asio::serial_port_base::flow_control::none
);

class SerialUSB : private boost::asio::noncopyable {
	enum {
		NSIZE = 512,
		SERIAL_BAUD = 115200
	};
	uint8_t data[NSIZE];

public:
	SerialUSB(const std::string &portname);
	virtual ~SerialUSB();

	void Open(SerialParams serialParams = SP_8N1);
	void Close();

	void Run();
private:
	boost::asio::io_service mIoService;
	boost::asio::serial_port mSerial;
	bool isOpen;
	std::string mPortName;

	void worker_thread(boost::asio::io_service &ios);
    void async_read();
    void received(const boost::system::error_code &ec, size_t bytesTransferred);
};

#endif