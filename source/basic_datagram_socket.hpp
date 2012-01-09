#ifndef _BASIC_DATAGRAM_SOCKET_HPP_
# define _BASIC_DATAGRAM_SOCKET_HPP_

# include "detail/socket_ops.hpp"
# include "detail/basic_socket.hpp"

# include "detail/datagram_socket_service.hpp"

namespace netio {

	template<typename Protocol, typename DatagramSocketService = detail::datagram_socket_service<Protocol> >
	class basic_datagram_socket
		: public detail::basic_socket<Protocol, DatagramSocketService>
	{

		typedef typename Protocol::endpoint endpoint_type;

		/// Methods.
	public:
		basic_datagram_socket(netio::io_service& io_service)
			: detail::basic_socket<Protocol, DatagramSocketService>(io_service)
		{;}	
		/*
		**
		*/
		basic_datagram_socket(netio::io_service& io_service, endpoint_type& endpoint)
			: detail::basic_socket<Protocol, DatagramSocketService>(io_service, endpoint)
		{;}
		/*
		**
		*/
		ssize_t recvfrom(
			endpoint_type& from,
			void* buffer,
			size_t len
		)
		{
			return this->_service.recvfrom(from, buffer, len);
		}
		/*
		**
		*/
		ssize_t sendto(
			endpoint_type& to,
			void* buffer,
			size_t len
		)
		{
			return this->_service.sendto(to, buffer, len);
		}
		/*
		**
		*/
		template<typename Buffer, typename ReadHandler>
		void async_recvfrom(
			endpoint_type& from,
			Buffer& buffer,
			size_t len,
			ReadHandler handler
		)
		{
			this->_service.async_recvfrom(from, buffer, len, handler);
		}

	};

} // !netio

#endif /* !_BASIC_DATAGRAM_SOCKET_HPP_ */