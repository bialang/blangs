#pragma once

#include <boost/asio.hpp>

namespace blangs {

class Server
{
public:
	Server(boost::asio::io_service& io_service);

private:
	boost::asio::ip::tcp::socket _socket;
	boost::asio::ip::tcp::acceptor _acceptor;

	void _queue_accept();
};

} // namespace blangs
