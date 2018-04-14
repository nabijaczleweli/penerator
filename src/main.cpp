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


#include "mongoose.hpp"
#include "ops.hpp"
#include "options/options.hpp"
#include <iostream>
#include <mongoose.h>


int main(int argc, const char ** argv) {
	const auto opts_r = penerator::options::parse(argc, argv);
	if(const auto error_val = nonstd::get_if<penerator::option_err>(&opts_r)) {
		std::cerr << error_val->second << '\n';
		return error_val->first;
	}
	const auto opts = std::move(nonstd::get<penerator::options>(opts_r));

	penerator::dev_urandom_gen generator;

	auto manager = penerator::mg_mgr_init(&generator);

	auto conn_r = penerator::mg_bind_or_err(manager.get(), opts.address, penerator::generic_event_handler);
	if(const auto error_val = nonstd::get_if<const char *>(&conn_r)) {
		std::cerr << "Couldn't open connection";
		if(error_val)
			std::cerr << ": " << *error_val;
		std::cerr << ".\n";

		return 17;
	}
	const auto conn = std::move(nonstd::get<mg_connection *>(conn_r));

	mg_set_protocol_http_websocket(conn);

	for(;;)
		mg_mgr_poll(manager.get(), 1000);
}
