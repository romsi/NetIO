#ifndef _IP_HPP_
# define _IP_HPP_

# include <sys/socket.h>
# include <netinet/in.h>

namespace netio {
namespace ip {

	// Obtain an identifier for the version of the protocol.
	static const int v4 = AF_INET;

} // !ip
} // !netio

#endif /* !_IP_HPP_ */