// The MIT License (MIT)

// Copyright (c) 2018 nabijaczleweli

// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


#include "mongoose.h"
#include "mongoose.hpp"
#include "options/options.hpp"
#include <iostream>


static void ev_handler(struct mg_connection * conn, int ev, void * ev_data) {
	std::cout << ev << '\n';
	if(ev == MG_EV_HTTP_REQUEST) {
		const auto & message = *static_cast<http_message *>(ev_data);
		std::cout << "message.message: \"\"\"" << std::string{message.message.p, message.message.len} << "\"\"\"\n";
		std::cout << "message.body: \"\"\"" << std::string{message.body.p, message.body.len} << "\"\"\"\n";
		std::cout << "message.method: \"\"\"" << std::string{message.method.p, message.method.len} << "\"\"\"\n";
		std::cout << "message.uri: \"\"\"" << std::string{message.uri.p, message.uri.len} << "\"\"\"\n";
		std::cout << "message.proto: \"\"\"" << std::string{message.proto.p, message.proto.len} << "\"\"\"\n";
		std::cout << "message.resp_code: " << message.resp_code << "\n";
		std::cout << "message.resp_status_msg: \"\"\"" << std::string{message.resp_status_msg.p, message.resp_status_msg.len} << "\"\"\"\n";
		std::cout << "message.query_string: \"\"\"" << std::string{message.query_string.p, message.query_string.len} << "\"\"\"\n";
		for(auto i = 0u; i < MG_MAX_HTTP_HEADERS; ++i)
			std::cout << "message.header_names[" << i << "]: \"\"\"" << std::string{message.header_names[i].p, message.header_names[i].len} << "\"\"\"\n";
		for(auto i = 0u; i < MG_MAX_HTTP_HEADERS; ++i)
			std::cout << "message.header_values[" << i << "]: \"\"\"" << std::string{message.header_values[i].p, message.header_values[i].len} << "\"\"\"\n";

		// We have received an HTTP request. Parsed request is contained in `message`.
		// Send HTTP reply to the client which shows full original request.
		mg_send_head(conn, 200, message.message.len, "Content-Type: text/plain");
		mg_printf(conn, "%.*s", (int)message.message.len, message.message.p);
	}
}


int main(int argc, const char ** argv) {
	const auto opts_r = penerator::options::parse(argc, argv);
	if(const auto error_val = nonstd::get_if<penerator::option_err>(&opts_r)) {
		std::cerr << error_val->second << '\n';
		return error_val->first;
	}
	const auto opts = std::move(nonstd::get<penerator::options>(opts_r));

	auto manager = penerator::mg_mgr_init(nullptr);
	const char * err{};
	mg_bind_opts bind_opts{};
	bind_opts.error_string = &err;
	auto conn              = mg_bind_opt(manager.get(), opts.address.c_str(), ev_handler, bind_opts);
	std::cout << conn << '\n';
	std::cout << (void *)err << '\n';
	if(err)
		std::cout << err << '\n';
	mg_set_protocol_http_websocket(conn);

	for(;;)
		mg_mgr_poll(manager.get(), 1000);
}
