#include "lsp.hpp"

using namespace blangs;

std::map<std::string, void (LSP::*)()> LSP::_methods;

void LSP::_handle_request(const Request_message& msg)
{
	auto method = _methods.find(msg.method);
	if (method == _methods.end()) {

	}
	// execute
	(this->*method->second)();
}
