#include <iostream>

#include <map>
#include <queue>

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

void recvfromHandler(netio::ip::udp::endpoint& endpoint, void* buffer, size_t bytes_transfered)
{
	std::cout << "Call recvfrom handler" << std::endl;
}

void server(netio::io_service& io_service)
{
	netio::ip::udp::endpoint endpoint(2442);
	netio::ip::udp::socket socket(io_service, endpoint);
	netio::ip::udp::endpoint from;
	char buffer[1024];
	/*
	** SYNC
	if (socket.recvfrom(from, buffer, sizeof(buffer)) > 0)
		std::cout << "MESSAGE : " << buffer << std::endl;
	else
		std::cout << "ERROR RECVFROM !" << std::endl;
	*/
	/*
	** ASYNC
	*/
	socket.async_recvfrom(from, buffer, sizeof(buffer), &recvfromHandler);
}

int main()
{
	netio::io_service io_service;
	std::cout << "Start" << std::endl;
	server(io_service);
	io_service.run();
	std::cout << "End" << std::endl;
}