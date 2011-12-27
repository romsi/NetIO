#ifndef _SOCKET_OPS_HPP_
# define _SOCKET_OPS_HPP_

# include <sys/types.h>
# include <poll.h>

# include "socket_types.hpp"

namespace netio {
namespace ip {
namespace detail {
namespace socket_ops {

	// Create an endpoint for communication.
	socket_type socket(
		int domain,
		int type,
		int protocol
	);

	// Bind a name to a socket.
	bool bind(
		socket_type sockfd,
		struct sockaddr *addr,
		socklen_t addrlen
	);

	// Receive a message from a socket.
	ssize_t recvfrom(
		socket_type sockfd,
		void *buffer,
		size_t len,
		int flags,
		struct sockaddr *addr,
		socklen_t *addrlen
	);

	ssize_t sync_recvfrom(
		socket_type sockfd,
		void *buffer,
		size_t len,
		int flags,
		struct sockaddr *addr,
		socklen_t *addrlen
	);

	// Send a message on a socket.
	ssize_t sendto(
		socket_type sockfd,
		const void* buffer,
		size_t len,
		int flags,
		const struct sockaddr *addr,
		socklen_t addrlen
	);

	ssize_t sync_sendto(
		socket_type sockfd,
		void *buffer,
		size_t len,
		int flags,
		struct sockaddr *addr,
		socklen_t addrlen
	);

	// Wait for some event on a file descriptor.
	int poll(
		struct pollfd *fds,
		nfds_t nfds,
		int timeout
	);

	bool poll_read(socket_type sockfd);

	bool poll_write(socket_type sockfd);

} // !socket_ops
} // !detail
} // !ip
} // !netio

#endif /* !_SOCKET_OPS_HPP_ */