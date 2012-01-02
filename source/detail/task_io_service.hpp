#ifndef _TASK_IO_SERVICE_HPP_
# define _TASK_IO_SERVICE_HPP_

namespace netio {
namespace detail {

	class task_io_service
	{

		/// Methods.
	public:
		task_io_service(netio::io_service& io_service)
			: _multiplexer(0)
		{;}
	
		/// Attributs.
	private:
		multiplexer* _multiplexer;
	};

} // !detail
} // !netio

#endif /* !_TASK_IO_SERVICE_HPP_ */