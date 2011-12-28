#ifndef _BASIC_DATAGRAM_SOCKET_HPP_
# define _BASIC_DATAGRAM_SOCKET_HPP_

# include "socket_ops.hpp"

# include "basic_socket.hpp"

namespace netio {

	template<class Protocol>
	class basic_datagram_socket
		: public detail::basic_socket<Protocol>
	{

		/// Methods.
	public:
		/*
		**
		*/
		basic_datagram_socket(typename Protocol::endpoint& endpoint)
			: detail::basic_socket<Protocol>(endpoint)
		{;}
		/*
		**
		*/
		ssize_t recvfrom(typename Protocol::endpoint& from, void* buffer, size_t len)
		{
			ssize_t bytes = 0;
			socklen_t size = from.size();
			return detail::socket_ops::sync_recvfrom(
				this->_socket,
				buffer,
				len,
				0,
				reinterpret_cast<struct sockaddr*>(from.data()),
				&size);
		}

	};

} // !netio

#endif /* !_BASIC_DATAGRAM_SOCKET_HPP_ */