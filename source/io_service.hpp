#ifndef _IO_SERVICE_HPP_
# define _IO_SERVICE_HPP_

# include "detail/socket_types.hpp"
# include "detail/task_io_service.hpp"
# include "detail/reactive_socket_service_fwd.hpp"
# include "detail/operation_type.hpp"
# include "detail/reactor_op.hpp"
# include "detail/multiplexer.hpp"

namespace netio {

	typedef detail::task_io_service task_service_type;

	class io_service
	{
		friend class detail::reactive_socket_service;

		typedef detail::operations::operation_type operation_type;
		typedef detail::reactor_op reactor_op;

		/// Methods.
	public:
		io_service()
		{;}
		/*
		**
		** @return The number of handlers that were executed.
		*/
		size_t run()
		{
			return _task.run();
		}
		/*
		**
		*/
		bool stop()
		{
			return _task.stop();
		}

	private:
		bool start_op(operation_type type, detail::socket_type& socket, reactor_op* op)
		{
			return _task.register_task(type, socket, op);
		}

		/// Attributs.
	private:
		task_service_type _task;

	}; // !io_service

} // !netio

#endif /* !_IO_SERVICE_HPP_ */