#ifndef _TASK_IO_SERVICE_HPP_
# define _TASK_IO_SERVICE_HPP_

# include "socket_types.hpp"
# include "operation_type.hpp"
# include "reactor_op.hpp"
# include "multiplexer.hpp"

namespace netio {

	class io_service;

	namespace detail {

		class task_io_service
		{

			typedef detail::operations::operation_type operation_type;

			/// Methods.
		public:
			task_io_service()
			{;}
			//
			size_t run()
			{
				return _multiplexer.run();
			}
			//
			bool stop()
			{
				// return _multiplexer.stop();
			}
			//
			bool register_task(operation_type type, socket_type& socket, reactor_op* op)
			{
				return _multiplexer.start_op(type, socket, op);
			}

			/// Attributs.
		private:
			multiplexer _multiplexer;
			

		}; // !task_io_service

	} // !detail

} // !netio

#endif /* !_TASK_IO_SERVICE_HPP_ */