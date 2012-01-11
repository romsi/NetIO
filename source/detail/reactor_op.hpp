#ifndef _REACTOR_OPERATION_HPP_
# define _REACTOR_OPERATION_HPP_

namespace netio {
namespace detail {

	class reactor_op
	{

	protected:
		typedef bool (*perform_func_type)(reactor_op*);
		typedef void (*complete_func_type)(reactor_op*, size_t);

		/// Methods.
	public:
		// Perform the operation. Returns true if it is finished.
		bool perform()
		{
			return _perform_func(this);
		}
		void complete()
		{
			_complete_func(this, _bytes_transferred);
		}

	protected:
		reactor_op(perform_func_type perform_func, complete_func_type complete_func)
			: _bytes_transferred(0),
		    _perform_func(perform_func),
		    _complete_func(complete_func)
		{;}

		/// Attributs.
	public:
		// The number of bytes transferred, to be passed to the completion handler.
		size_t _bytes_transferred;

	private:
		perform_func_type _perform_func;
		complete_func_type _complete_func;

	}; // !reactor_op

} // !detail
} // !netio

#endif /* !_REACTOR_OPERATION_HPP_ */