#pragma once

#include "types.hpp"

#include <boost/asio.hpp>
#include <ios>
#include <map>
#include <string>

namespace blangs {

class LSP
{
public:
	LSP(boost::asio::io_service& io_service, std::istream& input);

	/// Reads a request from the input stream and processes it asynchronously.
	void process()
	{
		json j;
		_input >> j;
		Request_message msg;
		j.get_to(msg);
		_io_service.post([this, msg] { _handle_request(msg); });
	}

private:
	static std::map<std::string, void(LSP::*)()> _methods;
	boost::asio::io_service& _io_service;
	std::istream _input;

	void _handle_request(const Request_message& msg);
};

} // namespace blangs
