#ifndef _IO_SERVICE_HPP_
# define _IO_SERVICE_HPP_

// # include "multiplexer.hpp"
// multiplexer* _multiplexer;

namespace netio {

// Pour enregistrer le reactor, penser au fonction friend.

	typedef detail::task_io_service task_service_type;

	class io_service
	{

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
			_task.stop();
		}

		/// Attributs.
	private:
		task_service_type _task;

	}; // !io_service

} // !netio

#endif /* !_IO_SERVICE_HPP_ */