#pragma once

#include <cstdint>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <variant>

using nlohmann::json;

namespace nlohmann {

template<typename... Types>
struct adl_serializer<std::variant<Types...>>
{
	static void to_json(json& j, const std::variant<Types...>& value)
	{
		((std::holds_alternative<Types>(value) && ((j = std::get<Types>(value)), true)) || ...);
	}
};

} // namespace nlohmann

namespace blangs {

typedef std::int32_t Integer;
typedef std::uint32_t Uinteger;
typedef json::object_t Object;
typedef json::array_t Array;

struct Message
{
	friend void to_json(json& j, Message)
	{
		j["jsonrpc"] = "2.0";
	}
	friend void from_json(const json& j, Message&)
	{
		if (j.at("jsonrpc").get<std::string>() != "2.0") {
			// TODO
		}
	}
};

struct Request_message : Message
{
	std::variant<Integer, std::string> id;
	std::string method;
	std::optional<std::variant<Array, Object>> params;

	friend void from_json(const json& j, Request_message& msg)
	{
		from_json(j, static_cast<Message&>(msg));
		j.at("method").get_to(msg.method);
		if (j.contains("params")) {
			
		}
	}
};

struct Response_error
{
	Integer code;
	std::string message;

	friend void to_json(json& j, const Response_error& msg)
	{
		j["code"]    = msg.code;
		j["message"] = msg.message;
	}
};

struct Response_message : Message
{
	std::variant<Integer, std::string, std::nullptr_t> id;
	std::optional<std::variant<std::string, std::int64_t, double, bool, Object, std::nullptr_t>> result;
	std::optional<Response_error> error;

	friend void to_json(json& j, const Response_message& msg)
	{
		to_json(j, static_cast<const Message&>(msg));
		j["id"] = msg.id;
		if (msg.result.has_value()) {
			j["result"] = msg.result.value();
		}
		if (msg.error.has_value()) {
			j["error"] = msg.error.value();
		}
	}
};

} // namespace blangs
