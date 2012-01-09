#ifndef _OPERATION_TYPE_HPP_
# define _OPERATION_TYPE_HPP_

namespace netio {
namespace detail {

	namespace operations {
		
		enum operation_type
		{
			write = 0,
			read,
			max_ops
		};

	} // ! operations

} // !detail
} // !netio

#endif /* !_OPERATION_TYPE_HPP_ */