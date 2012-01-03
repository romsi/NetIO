#ifndef _MULTIPLEXER_HPP_
# define _MULTIPLEXER_HPP_

namespace netio {
namespace detail {

	namespace operations {
		
		enum operation_type
		{
			write = 1,
			read
		};

	} // ! operations

	//typedef select_reactor multiplexer;

} // !detail
} // !netio

#endif /* !_MULTIPLEXER_HPP_ */