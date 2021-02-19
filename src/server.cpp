#include "server.hpp"

#include <spdlog/spdlog.h>

using namespace blangs;
using namespace boost::asio;

Server::Server(io_service& io_service)
    : _socket{ io_service }, _acceptor{ io_service, ip::tcp::endpoint{ ip::tcp::v4(), 6565 } }
{
	_queue_accept();
}

void Server::_queue_accept()
{
	_acceptor.async_accept(_socket, [this](const boost::system::error_code& error) {
		if (error) {
			spdlog::error("client failed to connect: {}", error.message());
		} else {
			spdlog::info("new client {}:{} connected", _socket.local_endpoint().address().to_string(),
			             _socket.local_endpoint().port());
									 
			_socket.close();
			_queue_accept();
		}
	});
}
