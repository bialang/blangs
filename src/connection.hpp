#pragma once

#include <boost/asio.hpp>
#include <cstddef>
#include <string>

namespace blangs {

class Connection
{
public:
	Connection(boost::asio::ip::tcp::socket socket);

private:
	struct Header
	{
		std::size_t content_length;
		std::string content_type;
	};

	boost::asio::ip::tcp::socket _socket;
	boost::asio::streambuf _buffer;

	void _queue_read();
	Header _parse_header(std::size_t size);
};

} // namespace blangs
