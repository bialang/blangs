#include "connection.hpp"

#include <spdlog/spdlog.h>

using namespace blangs;
using namespace boost::asio;

Connection::Connection(ip::tcp::socket socket) : _socket{ std::move(socket) }
{
	_queue_read();
}

void Connection::_queue_read()
{
	async_read_until(
	  _socket, _buffer, "\r\n\r\n",
	  [this](const boost::system::error_code& error, std::size_t bytes_transferred) {
		  if (error) {
			  spdlog::error("failed to read: {}", error.message());
		  } else {
			  spdlog::debug("received {} bytes of header", bytes_transferred);
			  const auto header = _parse_header(bytes_transferred);
			  spdlog::debug("Header{Length: {}, Type: '{}'}", header.content_length, header.content_type);
			  async_read(_socket, _buffer, transfer_exactly(header.content_length),
			             [this](const boost::system::error_code& error, std::size_t bytes_transferred) {
				             std::istream input{ &_buffer };
				             // TODO let LSP handle from here
				             _queue_read();
			             });
		  }
	  });
}

Connection::Header Connection::_parse_header(std::size_t size)
{
	Header header{};
	header.content_type = "application/vscode-jsonrpc; charset=utf-8";
	return header;
}
