#include "serialusb.hpp"

int main(int argc, char *argv[])
{
	std::string portname = "/dev/ttyUSB0";

	SerialUSB serialUsb(portname);
	serialUsb.Open();
	serialUsb.Run();

	return 0;
}