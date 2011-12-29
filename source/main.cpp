#include <iostream>

#include "ip/udp.hpp"

void client(netio::io_service& io_service)
{
	netio::ip::udp::socket socket(io_service);
	socket.open(netio::ip::udp::v4());
	netio::ip::udp::endpoint to(2442);
	char buffer[] = "test";
	if (socket.sendto(to, buffer, sizeof(buffer)) <= 0)
		std::cout << "ERROR SENDTO !" << std::endl;
}

void server(netio::io_service& io_service)
{
	netio::ip::udp::endpoint endpoint(2442);
	netio::ip::udp::socket socket(io_service, endpoint);
	netio::ip::udp::endpoint from;
	char buffer[1024];
	if (socket.recvfrom(from, buffer, sizeof(buffer)) > 0)
		std::cout << "MESSAGE : " << buffer << std::endl;
	else
		std::cout << "ERROR RECVFROM !" << std::endl;
}

int main()
{
	netio::io_service io_service;
	std::cout << "Start" << std::endl;
	server(io_service);
	std::cout << "End" << std::endl;
}