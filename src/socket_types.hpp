#ifndef _SOCKET_TYPES_HPP_
# define _SOCKET_TYPES_HPP_

namespace NetIO {
namespace detail {
namespace socket_ops {

typedef int socket_type;

const socket_type invalid_socket = -1;
const int socket_error = -1;

} // !socket_ops
} // !detail
} // !NetIO

#endif /* !_SOCKET_TYPES_HPP_ */