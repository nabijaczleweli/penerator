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


#pragma once


#include <fstream>
#include <mongoose.h>
#include <string>
#include <vector>


namespace penerator {
	extern const std::string bad_request_response;
	extern const std::vector<char> password_characters;


	/// A `UniformRandomBitGenerator` taking the `UniformRandomBit`s from `"/dev/urandom"`.
	class dev_urandom_gen {
	private:
		std::ifstream in;

	public:
		using result_type = std::uint8_t;

		dev_urandom_gen();
		operator bool() const;

		result_type min() const noexcept;
		result_type max() const noexcept;

		result_type operator()();
	};


	/// Event handler attachable to a connection.
	void generic_event_handler(mg_connection * conn, int ev, void * ev_data);

	/// Event handler for HTTP requests.
	void http_event_handler(mg_connection & conn, http_message & message);

	/// Generate a random password of `length` bytes.
	std::string generate_password(dev_urandom_gen & gen, std::size_t length);
}
