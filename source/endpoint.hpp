#ifndef _ENDPOINT_HPP_
# define _ENDPOINT_HPP_

#include <iostream>

# include <sys/socket.h>
# include <arpa/inet.h>
# include <netdb.h>

# include "socket_types.hpp"
# include "ip.hpp"

namespace netio {
namespace ip {

	class endpoint
	{

		/// Methods.
	public:
		endpoint()
		{
			_data.sin_family = ip::v4;
			_data.sin_port = 0;
			_data.sin_addr.s_addr = INADDR_ANY;
		}
		endpoint(in_port_t port_num)
		{
			_data.sin_family = ip::v4;
			_data.sin_port = htons(port_num);
			_data.sin_addr.s_addr = INADDR_ANY;	
		}
		endpoint(in_port_t port_num, const char* hostname)
		{
			struct hostent *hostinfo = gethostbyname(hostname);
			if (!hostinfo)
				std::cout << "Endpoint error." << std::endl;
			if (hostinfo)
			{
				_data.sin_family = ip::v4;
				_data.sin_port = htons(port_num);
				_data.sin_addr.s_addr = *(in_addr_t *)hostinfo->h_addr;	
			}
		}
		// Get the address family.
		int family() const
		{
			return _data.sin_family;
		}
		// Get the port of endpoint.
		in_port_t port() const
		{
			return ntohs(_data.sin_port);
		}
		// Set the port of endpoint.
		void port(in_port_t port_num)
		{
			_data.sin_port = htons(port_num);
		}
		// Get the size of native data.
		socklen_t size() const
		{
			return sizeof(_data);
		}
		// Get the native data.
		ip::detail::socket_ops::sockaddr_in4_type* data()
		{
			return &_data;
		}
		// Get the native data.
		const ip::detail::socket_ops::sockaddr_in4_type* data() const
		{
			return &_data;
		}

		/// Attributs.
	private:
		ip::detail::socket_ops::sockaddr_in4_type _data;

	};

} // !ip
} // !netio

#endif /* !_ENDPOINT_HPP_ */