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
			//
			bool isset(Descriptor& fd)
			{
				return FD_ISSET(fd, &data);
			}

			/// Attributs.
			fd_set data;

		}; // !fdset

		/// Methods.
	public:
		select_reactor()
		{;}
		bool start_op(operation_type type, socket_type& socket, reactor_op* op)
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
			// std::cout << "Max fd: " << max_fd << std::endl;
			bool has_work = !(max_fd == invalid_socket);
			if (!has_work)
			{
				std::cout << "No work" << std::endl;
				return 0;
			}
			std::cout << "Start select !" << std::endl;
			ssize_t ready = 0;
			if ((ready = ::select(max_fd + 1, &(_readfds.data), &(_writefds.data), 0, 0)) == -1)
				perror("select");
			std::cout << "Ending select !" << std::endl;
			has_work = !(ready == -1);
			if (!has_work)
				return 0;
			perform_operation(_readfds);
			perform_operation(_writefds);
			return ready;
		}
	private:
		void perform_operation(fdset<socket_type>& data)
		{
			std::queue<socket_type> descriptors = _op_queue[operations::read].get_descriptors();
			while (!descriptors.empty())
			{
				if (data.isset(descriptors.front()))
					_op_queue[operations::read].perform_operation(descriptors.front());
				descriptors.pop();
			}
		}

		/// Attributs.
	private:
		reactor_op_queue _op_queue[operations::max_ops];

		fdset<socket_type> _readfds;
		fdset<socket_type> _writefds;

	}; // !select_reactor

} // !detail
} // !netio

#endif /* !_SELECT_REACTOR_HPP_ */