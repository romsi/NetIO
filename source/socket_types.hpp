#ifndef _SOCKET_TYPES_HPP_
# define _SOCKET_TYPES_HPP_

namespace netio {
namespace ip {
namespace detail {
namespace socket_ops {

	typedef int socket_type;

	const socket_type invalid_socket = -1;
	const int socket_error = -1;

	typedef struct sockaddr_in sockaddr_in4_type;

} // !socket_ops
} // !detail
} // !dip
} // !NetIO

#endif /* !_SOCKET_TYPES_HPP_ */