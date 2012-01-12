#include <iostream>

#include <sys/socket.h>
#include <poll.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#include "../socket_types.hpp"
#include "../socket_ops.hpp"

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
		{
			perror("socket");
			return (detail::invalid_socket);
		}
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
			perror("bind");
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
			perror("recvfrom");
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
		}
	}

	ssize_t non_blocking_recvfrom(
		detail::socket_type sockfd,
		void *buffer,
		size_t len,
		int flags,
		struct sockaddr *addr,
		socklen_t *addrlen,
		size_t& bytes_transferred
	)
	{
		ssize_t bytes = 0;
		for (;;)
		{
			bytes = socket_ops::recvfrom(sockfd, buffer, len, flags, addr, addrlen);
			if (errno == EAGAIN || errno == EWOULDBLOCK)
			{
				std::cout << "Recvfrom EGAIN operation." << std::endl;
				return false;	
			}
			if (errno == EINTR)
				continue ;
			if (bytes >= 0)
			{
				bytes_transferred = bytes;
				return true;
			}
			bytes_transferred = 0;
			return true;
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
			perror("sendto");
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
		}
	}

	ssize_t non_blocking_sendto(
		detail::socket_type sockfd,
		void *buffer,
		size_t len,
		int flags,
		struct sockaddr *addr,
		socklen_t addrlen,
		size_t& bytes_transferred
	)
	{
		ssize_t bytes = 0;
		for (;;)
		{
			bytes = socket_ops::sendto(sockfd, buffer, len, flags, addr, addrlen);
			if (errno == EAGAIN || errno == EWOULDBLOCK)
			{
				std::cout << "Sendto EGAIN operation." << std::endl;
				return false;	
			}
			if (errno == EINTR)
				continue ;
			if (bytes >= 0)
			{
				bytes_transferred = bytes;
				return true;
			}
			bytes_transferred = 0;
			return true;
		}
	}

} // !socket_ops
} // !detail
} // !netio