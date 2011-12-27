#include <iostream>

#include "ip.hpp"
#include "endpoint.hpp"
#include "socket_ops.hpp"

void client(int s)
{
	netio::ip::endpoint to(2442, "localhost");
	char buffer[] = "test";
	if (netio::ip::detail::socket_ops::sendto(
		s,
		buffer,
		sizeof(buffer),
		0,
		reinterpret_cast<struct sockaddr*>(to.data()),
		to.size()) <= 0
	)
		std::cout << "SENDTO ERROR" << std::endl;
}

void server(int s)
{
	netio::ip::endpoint endpoint(2442);
	if (!netio::ip::detail::socket_ops::bind(
		s,
		reinterpret_cast<struct sockaddr*>(endpoint.data()),
		endpoint.size())
	)
		std::cout << "BIND ERROR" << std::endl;
	
	char buffer[1204];
	netio::ip::endpoint from;
	socklen_t size;
	// ERROR RECVFROM
	if (netio::ip::detail::socket_ops::recvfrom(
		s,
		buffer,
		sizeof(buffer),
		0,
		reinterpret_cast<struct sockaddr*>(from.data()),
		&size) <= 0
	)
		std::cout << "RECVFROM ERROR" << std::endl;
}

main()
{
	std::cout << "Start" << std::endl;
	int s = netio::ip::detail::socket_ops::socket(
		netio::ip::v4,
		netio::ip::udp::type,
		netio::ip::udp::protocol
	);
	if (s == netio::ip::detail::socket_ops::invalid_socket)
		std::cout << "SOCKET ERROR" << std::endl;

	server(s);
	std::cout << "End" << std::endl;
}