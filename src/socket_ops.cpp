#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>

#include "socket_types.hpp"

namespace NetIO {
namespace detail {
namespace socket_ops {

	inline socket_type socket(
		int domain,
		int type,
		int protocol
	)
	{
		socket_type s = ::socket(domain, type, protocol);
		if (s == invalid_socket)
			return (invalid_socket);
		return (s);
	}

	inline bool bind(
		socket_type sockfd,
		struct sockaddr *addr,
		socklen_t addrlen
	)
	{
		bool success = ::bind(sockfd, addr, addrlen);
		if (!success)
		{
			::close(sockfd);
			return (!success);
		}
		return (success);
	}

	inline ::ssize_t recvfrom(
		socket_type sockfd,
		void *buffer,
		size_t len,
		int flags,
		struct sockaddr *addr,
		socklen_t *addrlen
	)
	{
		::ssize_t bytes = ::recvfrom(sockfd, buffer, len, flags, addr, addrlen);
		return (bytes);
	}

	::ssize_t sync_recvfrom(
		socket_type sockfd,
		void *buffer,
		size_t len,
		int flags,
		struct sockaddr *addr,
		socklen_t *addrlen
	)
	{
		::ssize_t bytes = 0;

		for (;;)
		{
			bytes = socket_ops::recvfrom(sockfd, buffer, len, flags, addr, addrlen);
			if (bytes >= 0)
				return (bytes);
			if (!poll_read(sockfd))
				return (0);
		}
	}

	inline int poll(
		struct pollfd *fds,
		nfds_t nfds,
		int timeout
	)
	{
		int returns = ::poll(fds, nfds, timeout);
		return (returns);
	}

	bool poll_read(socket_type sockfd)
	{
		pollfd fds;
		fds.fd = sockfd;
		fds.events = POLLIN;
		fds.revents = 0;
		int result = socket_ops::poll(&fds, 1, -1);
		if (result == 0)
			return (false);
		else if (result == socket_error)
			return (false);
		return (true);
	}

} // !socket_ops
} // !detail
} // !NetIO