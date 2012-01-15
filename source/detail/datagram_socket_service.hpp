#ifndef _DATAGRAM_SOCKET_SERVICE_HPP_
# define _DATAGRAM_SOCKET_SERVICE_HPP_

# include "socket_types.hpp"
# include "reactor_op.hpp"
# include "reactive_socket_service.hpp"
# include "reactive_socket_recvfrom_op.hpp"
# include "reactive_socket_sendto_op.hpp"

# include "../io_service.hpp"

namespace netio {
namespace detail {

	template<typename Protocol>
	class datagram_socket_service
		: public reactive_socket_service
	{

	protected:
		typedef typename Protocol::endpoint endpoint_type;

		/// Methods.
	public:
		datagram_socket_service(netio::io_service& io_service)
			: reactive_socket_service(io_service)
		{;}
		//
		bool open(const Protocol& protocol)
		{
			_socket = socket_ops::socket(
				protocol.family(),
				protocol.type(),
				protocol.protocol()
			);
			return _socket != invalid_socket;
		}
		bool is_open() const
		{
			return _socket != invalid_socket;
		}
		//
		bool bind(endpoint_type& endpoint)
		{
			return socket_ops::bind(
				_socket,
				endpoint.data(),
				endpoint.size());
		}
		//
		bool close()
		{
			if (!is_open())
				return (true);
			bool success = socket_ops::close(_socket);
			_socket = invalid_socket;
			return success;
		}
		//
		ssize_t recvfrom(
			endpoint_type& from,
			void* buffer,
			size_t len
		)
		{
			socklen_t size = from.size();
			return detail::socket_ops::sync_recvfrom(
				_socket,
				buffer,
				len,
				0,
				from.data(),
				&size);
		}
		//
		ssize_t sendto(
			endpoint_type& to,
			void* buffer,
			size_t len
		)
		{
			return detail::socket_ops::sync_sendto(
				_socket,
				buffer,
				len,
				0,
				to.data(),
				to.size());
		}
		//
		template<typename Buffer, typename ReadHandler>
		void async_recvfrom(
			endpoint_type& from,
			Buffer& buffer,
			size_t len,
			ReadHandler handler
		)
		{
			reactor_op* op = new reactive_socket_recvfrom_op<Buffer, endpoint_type, ReadHandler>(_socket, from, buffer, len, handler);
			// start operation.
			this->start_op(operations::read, _socket, op);
		}
		//
		template<typename Buffer, typename WriteHandler>
		void async_sendto(
			endpoint_type& from,
			Buffer& buffer,
			size_t len,
			WriteHandler handler
		)
		{
			reactor_op* op = new reactive_socket_sendto_op<Buffer, endpoint_type, WriteHandler>(_socket, from, buffer, len, handler);
			// start operation.
			this->start_op(operations::write, _socket, op);
		}

		/// Attributs.
	private:
		socket_type _socket;
		
	};

} // !detail
} // !netio

#endif /* !_DATAGRAM_SOCKET_SERVICE_HPP_ */