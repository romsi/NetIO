#ifndef _REACTIVE_SOCKET_SERVICE_HPP_
# define _REACTIVE_SOCKET_SERVICE_HPP_

# include "socket_types.hpp"
# include "reactor_op.hpp"

# include "../io_service.hpp"

namespace netio {
namespace detail {

	class reactive_socket_service
	{

		/// Methods.
	public:
		reactive_socket_service(netio::io_service& io_service)
			: _service(io_service)
		{;}
		//
		bool start_op(operations::operation_type type, reactor_op* op)
		{
			return _service.register_task(type, op);
		}

		/// Attributs.
	private:
		netio::io_service& _service;

	};

} // !detail
} // !netio

#endif /* !_REACTIVE_SOCKET_SERVICE_HPP_ */