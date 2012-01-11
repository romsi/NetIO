#ifndef _REACTIVE_SOCKET_RECVFROM_HPP_
# define _REACTIVE_SOCKET_RECVFROM_HPP_

# include "socket_types.hpp"
# include "reactor_op.hpp"

namespace netio {
namespace detail {

	template<typename Buffer, typename Endpoint, typename Handler>
	class reactive_socket_recvfrom_op
		: public reactor_op
	{

	public:
		reactive_socket_recvfrom_op(
			socket_type& socket,
			Endpoint& endpoint,
			Buffer& buffer,
			size_t len,
			Handler handler
		)
			: reactor_op(
				&reactive_socket_recvfrom_op::do_perform,
				&reactive_socket_recvfrom_op::do_complete
			),
			_socket(socket),
			_endpoint(endpoint),
			_buffer(buffer),
			_len(len),
			_handler(handler)
		{;}
		//
		static bool do_perform(reactor_op* base)
		{
			reactive_socket_recvfrom_op* op(static_cast<reactive_socket_recvfrom_op*>(base));
			size_t addrlen = op->_endpoint.size();
			return socket_ops::non_blocking_recvfrom(
				op->_socket,
		      	op->_buffer,
		      	op->_len,
		      	0,
		      	op->_endpoint.data(),
		      	&addrlen,
		      	op->_bytes_transferred);
		}
		//
		static void do_complete(reactor_op* base, size_t bytes_transferred)
		{
			reactive_socket_recvfrom_op* op(static_cast<reactive_socket_recvfrom_op*>(base));
			op->_handler(op->_endpoint, op->_buffer, bytes_transferred);
		}

		/// Attributs.
	private:
		socket_type _socket;
		Endpoint _endpoint;
		Buffer _buffer;
		size_t _len;
		Handler _handler;

	};

} // !detail
} // !netio

#endif /* !_REACTIVE_SOCKET_RECVFROM_HPP_ */