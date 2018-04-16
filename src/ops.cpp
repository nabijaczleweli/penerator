// The MIT License (MIT)

// Copyright (c) 2018 nabijaczleweli

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.


#include "ops.hpp"
#include "util/ops.hpp"
#include "util/log.hpp"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <random>
#include <string>


const char * const penerator::response_headers = "Content-Type: text/plain\r\n"
                                                 "Cache-Control: no-cache\r\n"
                                                 "Server: penerator/" PENERATOR_VERSION;

const std::string penerator::bad_request_response = "400 Bad Request";

const std::vector<char> penerator::password_characters = []() {
	const auto str = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890~!`@#$%^&*()_+-=[]\\{}|;':\",./<>?";
	return std::vector<char>{str, str + std::strlen(str)};
}();


penerator::dev_urandom_gen::dev_urandom_gen() : in("/dev/urandom", std::ios::binary) {}

penerator::dev_urandom_gen::operator bool() const {
	return static_cast<bool>(in);
}

penerator::dev_urandom_gen::result_type penerator::dev_urandom_gen::min() const noexcept {
	return 0x00;
}

penerator::dev_urandom_gen::result_type penerator::dev_urandom_gen::max() const noexcept {
	return 0xFF;
}

penerator::dev_urandom_gen::result_type penerator::dev_urandom_gen::operator()() {
	return in.get();
}


void penerator::generic_event_handler(mg_connection * conn, int ev, void * ev_data) {
	if(ev == MG_EV_HTTP_REQUEST && conn != nullptr)
		http_event_handler(*conn, *static_cast<http_message *>(ev_data));
}

void penerator::http_event_handler(mg_connection & conn, http_message & message) {
	if(message.uri.len == 1 &&                  // Equivalent to checking for uri == "/"
	   mg_vcmp(&message.method, "GET") == 0 &&  //
	   verify_password_length(message.query_string.p, message.query_string.len)) {
		const auto length = std::strtoul(message.query_string.p, nullptr, 10);

		//             255 .   255 .   255 .  255  :   65535
		char remote_ip[3 + 1 + 3 + 1 + 3 + 1 + 3 + 1 + 5 + 1]{};
		mg_conn_addr_to_str(&conn, remote_ip, sizeof(remote_ip) / sizeof(*remote_ip), MG_SOCK_STRINGIFY_IP | MG_SOCK_STRINGIFY_PORT | MG_SOCK_STRINGIFY_REMOTE);
		std::cout << date_prefix << " Serving " << length << " characters to " << remote_ip << ".\n";

		const auto password = generate_password(*static_cast<dev_urandom_gen *>(conn.mgr->user_data), length);

		mg_send_head(&conn, 200, password.size(), response_headers);
		mg_send(&conn, password.c_str(), password.size());
	} else {
		mg_send_head(&conn, 400, bad_request_response.size(), response_headers);
		mg_send(&conn, bad_request_response.c_str(), bad_request_response.size());
	}
}

std::string penerator::generate_password(dev_urandom_gen & gen, std::size_t length) {
	std::string ret(length, '\0');
	std::uniform_int_distribution<std::size_t> dist(0, password_characters.size() - 1);

	std::generate(std::begin(ret), std::end(ret), [&]() { return password_characters[dist(gen)]; });

	return ret;
}
