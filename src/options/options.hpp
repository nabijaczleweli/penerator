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


#pragma once


#include <nonstd/variant.hpp>
#include <utility>


namespace penerator {
	using option_err = std::pair<int, std::string>;

	/// Representation of command-line configurable application parameters.
	struct options {
		/// Address to bind to, in the `"[[IP_ADDRESS]:]PORT"` format.
		///
		/// Default: `"8000"`.
		std::string address;


		/// Attempt to parse command-line arguments.
		///
		/// On success, returns `{parsed_opts, 0, whatever}`.
		///
		/// On error, returns `{_invalid_, exit code != 0, error message}`.
		static nonstd::variant<options, option_err> parse(int argc, const char * const * argv);
	};

	bool operator==(const options & lhs, const options & rhs);
	bool operator!=(const options & lhs, const options & rhs);
}
