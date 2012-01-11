#ifndef _REACTIVE_SOCKET_SERVICE_HPP_
# define _REACTIVE_SOCKET_SERVICE_HPP_

# include "socket_types.hpp"
# include "operation_type.hpp"
# include "reactor_op.hpp"

# include "../io_service.hpp"

namespace netio {
namespace detail {

	class reactive_socket_service
	{

		typedef detail::operations::operation_type operation_type;

		/// Methods.
	public:
		reactive_socket_service(netio::io_service& io_service)
			: _service(io_service)
		{;}
		//
		bool start_op(operation_type type, socket_type& socket, reactor_op* op)
		{
			return _service.start_op(type, socket, op);
		}

		/// Attributs.
	private:
		netio::io_service& _service;

	};

} // !detail
} // !netio

#endif /* !_REACTIVE_SOCKET_SERVICE_HPP_ */