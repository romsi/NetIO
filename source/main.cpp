#include <iostream>

#include "udp.hpp"

void client()
{
	netio::ip::udp::socket socket;
	socket.open(netio::ip::udp::v4());
	netio::ip::udp::endpoint to(2442);
	char buffer[] = "test";
	if (socket.sendto(to, buffer, sizeof(buffer)) <= 0)
		std::cout << "ERROR SENDTO !" << std::endl;
}

void server()
{
	netio::ip::udp::endpoint endpoint(2442);
	netio::ip::udp::socket socket(endpoint);
	netio::ip::udp::endpoint from;
	char buffer[1024];
	if (socket.recvfrom(from, buffer, sizeof(buffer)) > 0)
		std::cout << "MESSAGE : " << buffer << std::endl;
	else
		std::cout << "ERROR RECVFROM !" << std::endl;
}

int main()
{
	std::cout << "Start" << std::endl;
	server();
	std::cout << "End" << std::endl;
}