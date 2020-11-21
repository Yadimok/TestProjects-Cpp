#include "serialusb.hpp"

SerialUSB::SerialUSB(const std::string& portname) : mIoService(), mSerial(mIoService)
{
	isOpen = false;
	mPortName = portname;
}

SerialUSB::~SerialUSB()
{
	Close();
}

void SerialUSB::Open(SerialParams serialParams)
{

	try {
		mSerial.open(mPortName);
	} catch (std::exception &exc) {
		std::cout << exc.what() << std::endl;
	}

	mSerial.set_option(boost::asio::serial_port_base::baud_rate(SERIAL_BAUD));
	mSerial.set_option(serialParams.get<0>());
	mSerial.set_option(serialParams.get<1>());
	mSerial.set_option(serialParams.get<2>());
	mSerial.set_option(serialParams.get<3>());

	isOpen = true;

	async_read();
}

void SerialUSB::Close()
{
	if (isOpen) {
		isOpen = false;
		mSerial.cancel();
		mSerial.close();

		mIoService.stop();
		mIoService.reset();
	}
}

void SerialUSB::async_read() {
    mSerial.async_read_some(boost::asio::buffer(data, NSIZE),
                boost::bind(&SerialUSB::received, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
}

void SerialUSB::received(const boost::system::error_code &ec, 
                        size_t bytesTransferred) {
    if (!ec) {
        if (bytesTransferred > 0) {
            data[bytesTransferred] = '\0';
            std::cout << data;
        }

        async_read();
    } else {
        Close();
    }
}

void SerialUSB::Run()
{
    
    boost::thread_group workerThreads;
    for (unsigned int i=0; i<boost::thread::hardware_concurrency(); i++)
    {
        workerThreads.create_thread(boost::bind(&SerialUSB::worker_thread, 
                                                this,
                                                boost::ref(mIoService)));
    }

    workerThreads.join_all();
}

void SerialUSB::worker_thread(boost::asio::io_service &ios)
{    
    while(true) {
        try {
            boost::system::error_code ec;
            ios.run(ec);
        } catch (const std::exception &exc) {
            std::cout << exc.what() << std::endl;
        }
    }
}