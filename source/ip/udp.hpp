#ifndef _UDP_HPP_
# define _UDP_HPP_

# include <sys/socket.h>
# include <netinet/in.h>

# include "ip.hpp"
# include "detail/endpoint.hpp"
# include "../basic_datagram_socket.hpp"

namespace netio {
namespace ip {

	class udp
	{
		/// Typedef
	public:
		typedef basic_datagram_socket<udp> socket;
		typedef detail::endpoint<udp> endpoint;

		/// Methods.
	public:
		static udp v4()
		{
			return udp(ip::v4);
		}
		// Obtain an identifier for the family of the protocol.
		int family() const
		{
			return _family;
		}
		// Obtain an identifier for the type of the protocol.
		int type() const
		{
			return SOCK_DGRAM;
		}
		// Obtain an identifier for the protocol.
		int protocol() const
		{
			return IPPROTO_UDP;
		}
	private:
		explicit udp(int protocol_family) : _family(protocol_family)
		{;}

		/// Attributs.
  	private:
  		int _family;

	}; // !udp

} // !ip
} // !netio

#endif /* !_UDP_HPP_ */