#ifndef _IO_SERVICE_HPP_
# define _IO_SERVICE_HPP_

namespace netio {

// Pour enregistrer le reactor, penser au fonction friend.

	class io_service
	{

		/// Methods.
	public:
		io_service()
		{;}
		bool run();
		bool poll();
		bool stop();

		/// Attributs.
	private:
		// reactor* _reactor;

	}; // !io_service

} // !netio

#endif /* !_IO_SERVICE_HPP_ */