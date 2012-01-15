#ifndef _SOCKET_OPS_HPP_
# define _SOCKET_OPS_HPP_

# include <sys/types.h>
# include <poll.h>

# include "socket_types.hpp"

namespace netio {
namespace detail {
namespace socket_ops {

	// Create an endpoint for communication.
	detail::socket_type socket(
		int domain,
		int type,
		int protocol
	);

	// Close a socket.
	bool close(detail::socket_type sockfd);

	// Bind a name to a socket.
	bool bind(
		detail::socket_type sockfd,
		struct sockaddr *addr,
		socklen_t addrlen
	);

	// Receive a message from a socket.
	ssize_t recvfrom(
		detail::socket_type sockfd,
		void *buffer,
		size_t len,
		int flags,
		struct sockaddr *addr,
		socklen_t *addrlen
	);

	ssize_t sync_recvfrom(
		detail::socket_type sockfd,
		void *buffer,
		size_t len,
		int flags,
		struct sockaddr *addr,
		socklen_t *addrlen
	);

	//
	ssize_t non_blocking_recvfrom(
		detail::socket_type sockfd,
		void *buffer,
		size_t len,
		int flags,
		struct sockaddr *addr,
		socklen_t *addrlen,
		size_t& bytes_transferred
	);

	// Send a message on a socket.
	ssize_t sendto(
		detail::socket_type sockfd,
		const void* buffer,
		size_t len,
		int flags,
		const struct sockaddr *addr,
		socklen_t addrlen
	);

	ssize_t sync_sendto(
		detail::socket_type sockfd,
		void *buffer,
		size_t len,
		int flags,
		struct sockaddr *addr,
		socklen_t addrlen
	);

	//
	ssize_t non_blocking_sendto(
		detail::socket_type sockfd,
		void *buffer,
		size_t len,
		int flags,
		struct sockaddr *addr,
		socklen_t addrlen,
		size_t& bytes_transferred
	);

	// Wait for some event on a file descriptor.
	int poll(
		struct pollfd *fds,
		nfds_t nfds,
		int timeout
	);

	bool poll_read(detail::socket_type sockfd);

	bool poll_write(detail::socket_type sockfd);

} // !socket_ops
} // !detail
} // !netio

#endif /* !_SOCKET_OPS_HPP_ */