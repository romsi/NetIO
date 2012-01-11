#ifndef _BASIC_SOCKET_HPP_
# define _BASIC_SOCKET_HPP_

# include "socket_types.hpp"
# include "socket_ops.hpp"

# include "../io_service.hpp"

namespace netio {
namespace detail {

	template<typename Protocol, typename Service>
	class basic_socket
	{

		typedef typename Protocol::endpoint endpoint_type;

		/// Methods.
	public:
		basic_socket(netio::io_service& io_service)
			: _service(io_service)
		{;}
		/*
		**
		*/
		basic_socket(netio::io_service& io_service, endpoint_type& endpoint)
			: _service(io_service)
		{
			Protocol protocol = endpoint.protocol();
			if (!open(protocol))
				std::cout << "OPEN ERROR" << std::endl;
			// On error, throw exception.
			if (!bind(endpoint))
				std::cout << "BIND ERROR" << std::endl;
			// On error, throw exception.
		}
		/*
		**
		*/
		bool open(const Protocol& protocol)
		{
			return _service.open(protocol);
		}
		/*
		**
		*/
		bool is_open() const
		{
			return _service.is_open();
		}
		/*
		**
		*/
		bool bind(endpoint_type& endpoint)
		{
			return _service.bind(endpoint);
		}
		/*
		**
		*/
		bool close()
		{
			return _service.close();
		}

		/// Attributs.
	protected:
		Service _service;

	}; // !basic_socket

} // !detail
} // !netio

#endif /* !_BASIC_SOCKET_HPP_ */