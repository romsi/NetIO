#include <iostream>

#include <sys/socket.h>
#include <poll.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#include "socket_types.hpp"
#include "socket_ops.hpp"

namespace netio {
namespace detail {
namespace socket_ops {

	detail::socket_type socket(
		int domain,
		int type,
		int protocol
	)
	{
		detail::socket_type sockfd = ::socket(domain, type, protocol);
		if (sockfd == detail::invalid_socket)
			return (detail::invalid_socket);
		return (sockfd);
	}

	bool close(detail::socket_type sockfd)
	{
		return (::close(sockfd) == 0) ? true : false;
	}

	bool bind(
		detail::socket_type sockfd,
		struct sockaddr *addr,
		socklen_t addrlen
	)
	{
		if (::bind(sockfd, addr, addrlen) == -1)
		{
			::close(sockfd);
			return (false);
		}
		return (true);
	}

	ssize_t recvfrom(
		detail::socket_type sockfd,
		void *buffer,
		size_t len,
		int flags,
		struct sockaddr *addr,
		socklen_t *addrlen
	)
	{
		ssize_t bytes = ::recvfrom(sockfd, buffer, len, flags, addr, addrlen);
		if (bytes == -1)
		{
			switch (errno)
			{
				case EBADF : std::cout << "EBADF" << std::endl; break;
				case EAGAIN : std::cout << "EAGAIN" << std::endl; break;
				case ECONNREFUSED : std::cout << "ECONNREFUSED" << std::endl; break;
				case EFAULT : std::cout << "EFAULT" << std::endl; break;
				case EINTR : std::cout << "EINTR" << std::endl; break;
				case EINVAL : std::cout << "EINVAL" << std::endl; break;
				case ENOMEM : std::cout << "ENOMEM" << std::endl; break;
				case ENOTCONN : std::cout << "ENOTCONN" << std::endl; break;
				case ENOTSOCK : std::cout << "ENOTSOCK" << std::endl; break;
				default : std::cout << "Error inconnu !" << std::endl; break;
			}
		}
		return (bytes);
	}

	ssize_t sync_recvfrom(
		detail::socket_type sockfd,
		void *buffer,
		size_t len,
		int flags,
		struct sockaddr *addr,
		socklen_t *addrlen
	)
	{
		ssize_t bytes = 0;

		for (;;)
		{
			bytes = socket_ops::recvfrom(sockfd, buffer, len, flags, addr, addrlen);
			if (bytes >= 0)
				return (bytes);
			std::cout << "POLL READ" << std::endl;
			if (!socket_ops::poll_read(sockfd))
				return (0);
		}
	}

	ssize_t sendto(
		detail::socket_type sockfd,
		const void* buffer,
		size_t len,
		int flags,
		const struct sockaddr *addr,
		socklen_t addrlen
	)
	{
		ssize_t bytes = ::sendto(sockfd, buffer, len, flags, addr, addrlen);
		if (!(bytes >= 0))
			std::cout << "ERROR detail::sendto" << std::endl;
		return (bytes);
	}

	ssize_t sync_sendto(
		detail::socket_type sockfd,
		void *buffer,
		size_t len,
		int flags,
		struct sockaddr *addr,
		socklen_t addrlen
	)
	{
		ssize_t bytes = 0;
		for (;;)
		{
			bytes = socket_ops::sendto(sockfd, buffer, len, flags, addr, addrlen);
			if (bytes >= 0)
				return (bytes);
			std::cout << "POLL WRITE" << std::endl;
			if (!socket_ops::poll_write(sockfd))
				return (0);
		}
	}

	int poll(
		struct pollfd *fds,
		nfds_t nfds,
		int timeout
	)
	{
		int returns = ::poll(fds, nfds, timeout);
		return (returns);
	}

	bool poll_read(detail::socket_type sockfd)
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

	bool poll_write(detail::socket_type sockfd)
	{
		pollfd fds;
		fds.fd = sockfd;
		fds.events = POLLOUT;
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
} // !netio