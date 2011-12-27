#ifndef _IP_HPP_
# define _IP_HPP_

# include <sys/socket.h>
# include <netinet/in.h>

# include "ip.hpp"

namespace netio {
namespace ip {

	struct udp {

		// Obtain an identifier for the type of the protocol.
		static const int type = SOCK_DGRAM;
		// Obtain an identifier for the protocol.
  		static const int protocol = IPPROTO_UDP;

	}; // !udp

} // !ip
} // !netio

#endif /* !_IP_HPP_ */