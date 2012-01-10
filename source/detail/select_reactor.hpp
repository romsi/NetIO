#ifndef _SELECT_REACTOR_HPP_
# define _SELECT_REACTOR_HPP_

# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

# include <stdio.h>
# include <errno.h>

# include "socket_types.hpp"
# include "operation_type.hpp"
# include "reactor_op.hpp"
# include "reactor_op_queue.hpp"

namespace netio {
namespace detail {

	class select_reactor
	{

		typedef detail::operations::operation_type operation_type;

		/// Methods.
	public:
		select_reactor()
		{;}
		bool start_op(operation_type type, socket_type socket, reactor_op* op)
		{
			return _op_queue[type].enqueue(socket, op);
		}
		//
		bool register_descriptor();
		//
		size_t run()
		{
			socket_type max_readfd = _readfds.set_all(_op_queue[operations::read].get_descriptors());
			socket_type max_writefd = _writefds.set_all(_op_queue[operations::write].get_descriptors());
			socket_type max_fd = (max_readfd > max_writefd) ? max_readfd : max_writefd;
			std::cout << "Max fd: " << max_fd << std::endl;
			_op_queue[operations::read].perform_operation(max_fd);
			ssize_t ready = 0;
			if ((ready = ::select(max_fd + 1, &(_readfds.data), &(_writefds.data), 0, 0)) == -1)
				perror("select");
			std::cout << "Descriptor ready: " << ready << std::endl;
			return (ready == -1) ? 0 : ready;
		}

		/// Attributs.
	private:
		reactor_op_queue _op_queue[operations::max_ops];

		template<typename Descriptor>
		struct fdset
		{

			/// Methods.
			fdset()
			{
				FD_ZERO(&data);
			}
			//
			socket_type set_all(std::queue<Descriptor> descriptors)
			{
				FD_ZERO(&data);
				socket_type max_fd = invalid_socket;
				while (!descriptors.empty())
				{
					if (descriptors.front() > max_fd)
						max_fd = descriptors.front();
					set(descriptors.front());
					descriptors.pop();
				}
				return max_fd;
			}
			//
			void set(Descriptor& fd)
			{
				std::cout << "FD: " << fd << std::endl;
				FD_SET(fd, &data);
			}

			/// Attributs.
			fd_set data;

		};

		fdset<socket_type> _readfds;
		fdset<socket_type> _writefds;

	}; // !select_reactor

} // !detail
} // !netio

#endif /* _SELECT_REACTOR_HPP_ */