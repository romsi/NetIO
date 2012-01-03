#ifndef _TASK_IO_SERVICE_HPP_
# define _TASK_IO_SERVICE_HPP_

# include <queue>

# include "reactor_op.hpp"
# include "multiplexer.hpp"

namespace netio {

	class io_service;

	namespace detail {

	// Pour enregistrer le reactor, penser au fonction friend.

		class task_io_service
		{

			/// Methods.
		public:
			task_io_service()
				// : _multiplexer(0)
			{;}
			//
			size_t run()
			{
				// return _multiplexer.run(_op_queue);
			}
			bool stop()
			{
				;
			}
			bool register_task(operations::operation_type type, reactor_op* op)
			{
				;
			}

			/// Attributs.
		private:
			//multiplexer* _multiplexer;
			std::queue<reactor_op> _op_queue;

		}; // !task_io_service

	} // !detail

} // !netio

#endif /* !_TASK_IO_SERVICE_HPP_ */