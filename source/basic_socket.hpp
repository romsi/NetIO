#ifndef _BASIC_SOCKET_HPP_
# define _BASIC_SOCKET_HPP_

# include "socket_types.hpp"
# include "socket_ops.hpp"

namespace netio {
namespace detail {

	template<class Protocol>
	class basic_socket
	{
		/// Methods.
	public:
		basic_socket() : _socket(invalid_socket)
		{;}
		/*
		**
		*/
		basic_socket(typename Protocol::endpoint& endpoint)
			: _socket(invalid_socket)
		{
			Protocol protocol = endpoint.protocol();
			if (!open(protocol))
				std::cout << "OPEN ERROR" << std::endl;
			// On error, throw exception.
			if (!bind(endpoint))
				std::cout << "BIND ERROR" << std::endl;
			// On error, throw exception.
		}
		~basic_socket()
		{
			if (!close())
				std::cout << "CLOSE ERROR" << std::endl;
		}
		/*
		**
		*/
		bool open(const Protocol& protocol)
		{
			_socket = socket_ops::socket(
				protocol.family(),
				protocol.type(),
				protocol.protocol()
			);
			return (_socket == invalid_socket) ? false : true;
		}
		bool is_open() const
		{
			return _socket != invalid_socket;
		}
		/*
		**
		*/
		bool bind(typename Protocol::endpoint& endpoint)
		{
			return socket_ops::bind(
				_socket,
				reinterpret_cast<struct sockaddr*>(endpoint.data()),
				endpoint.size());
		}
		/*
		**
		*/
		bool close()
		{
			if (!is_open())
				return (true);
			bool success = socket_ops::close(_socket);
			_socket = invalid_socket;
			return success;
		}

		/// Attributs.
	protected:
		socket_type _socket;

	}; // !basic_socket

} // !detail
} // !netio

#endif /* !_BASIC_SOCKET_HPP_ */