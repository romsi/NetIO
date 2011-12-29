#ifndef _REACTIVE_SOCKET_SERVICE_HPP_
# define _REACTIVE_SOCKET_SERVICE_HPP_

# include "socket_types.hpp"
# include "reactor_op.hpp"
// # include "multiplexer.hpp"

# include "../io_service.hpp"

namespace netio {
namespace detail {

	// A mettre dans le reactor.
	namespace operations {
		
		enum operation_type
		{
			write = 1,
			read
		};

	}

	class reactive_socket_service
	{

	public:
		reactive_socket_service(netio::io_service& io_service)
			// : _multiplexer(io_service)
		{;}
		//
		bool start_op(operations::operation_type type, socket_type socket, reactor_op* op)
		{
			// _multiplexer.start_op(type, socket, op);
			return true;
		}

	private:
		// multiplexer _multiplexer;

	};

} // !detail
} // !netio

#endif /* !_REACTIVE_SOCKET_SERVICE_HPP_ */