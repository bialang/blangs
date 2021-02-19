#include "server.hpp"
#include "types.hpp"

#include <CLI/CLI.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <spdlog/spdlog.h>
#include <thread>
#include <vector>

int main(int argc, char** argv)
{
	spdlog::set_level(spdlog::level::trace);
	CLI::App app;
	unsigned int thread_count = 1;

	app.add_option("-t,--threads", thread_count, "The amount of worker threads", true);

	CLI11_PARSE(app, argc, argv);

	boost::asio::io_service io_service;
	std::vector<std::thread> workers;
	boost::asio::io_service::work work{ io_service };
	blangs::Server server{ io_service };

	// launch
	if (thread_count == 0) {
		thread_count = std::thread::hardware_concurrency();
	}
	for (unsigned int i = 1; i < thread_count; ++i) {
		workers.push_back(std::thread{ [&] {
			spdlog::trace("launching worker");
			io_service.run();
		} });
	}
	io_service.run();
	for (auto& worker : workers) {
		worker.join();
	}
}
