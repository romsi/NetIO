#ifndef _REACTOR_OP_QUEUE_HPP_
# define _REACTOR_OP_QUEUE_HPP_

# include <iostream>

# include <queue>
# include <map>

# include "reactor_op.hpp"

namespace netio {
namespace detail {

	class reactor_op_queue
	{

		typedef std::queue<reactor_op*> op_queue_type;
		typedef std::map<socket_type, op_queue_type*> op_map_type;


		/// Methods.
	public:
		reactor_op_queue()
		{;}
		//
		bool enqueue(socket_type& socket, reactor_op* op)
		{
			std::pair<op_map_type::iterator, bool> ret = _op_map.insert(op_map_type::value_type(socket, new op_queue_type));
			ret.first->second->push(op);
			return true;
		}
		//
		std::queue<socket_type> get_descriptors() const
		{
			std::queue<socket_type> descriptors;
			for (op_map_type::const_iterator i = _op_map.begin(); i != _op_map.end(); i++)
    			descriptors.push((*i).first);
			return descriptors;
		}
		bool empty() const
		{
			return _op_map.empty();
		}
		//
		bool perform_operation(socket_type& socket)
		{
			op_map_type::iterator i = _op_map.find(socket);
			if (i != _op_map.end())
			{

				while (!(*i).second->empty())
				{
					if (!((*i).second->front()->perform()))
					{
						std::cout << "Perform failed !" << std::endl;
						return false;	
					}
					(*i).second->front()->complete();
					delete (*i).second->front();
					(*i).second->pop();	
				}
				_op_map.erase(i);
				return true;
			}
			return false;
		}
		
		/// Attributs.
	private:
		op_map_type _op_map;

	}; // !reactor_op_queue

} // !detail
} // !netio

#endif /* _REACTOR_OP_QUEUE_HPP_ */