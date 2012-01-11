#ifndef _ENDPOINT_HPP_
# define _ENDPOINT_HPP_

#include <iostream>

# include <sys/socket.h>
# include <arpa/inet.h>
# include <netdb.h>

# include "../../detail/socket_types.hpp"
# include "../ip.hpp"

namespace netio {
namespace ip {
namespace detail {

	template<class InternetProtocol>
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
		endpoint(const endpoint& e)
		{
			(*this) = e;
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
		endpoint& operator=(const endpoint& e)
		{
			_data = e._data;
			return (*this);
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
		struct sockaddr* data()
		{
			return reinterpret_cast<struct sockaddr*>(&_data);
		}
		// Get the native data.
		const netio::detail::sockaddr_in4_type* data() const
		{
			return reinterpret_cast<struct sockaddr*>(&_data);
		}
		InternetProtocol protocol() const
		{
			return InternetProtocol::v4();
		}

		/// Attributs.
	private:
		netio::detail::sockaddr_in4_type _data;

	}; // !endpoint

} // !detail
} // !ip
} // !netio

#endif /* !_ENDPOINT_HPP_ */