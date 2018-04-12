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


#include "options.hpp"
#include "constraints.hpp"
#include <tclap/CmdLine.h>
#include <tclap/ValueArg.h>


nonstd::variant<penerator::options, penerator::option_err> penerator::options::parse(int argc, const char * const * argv) {
	options ret{};

	try {
		penerator::bind_address_constraint address_constraint("[[IP_ADDRESS]:]PORT");

		TCLAP::CmdLine command_line("penerator -- Generate a secure password over your local network", ' ', PENERATOR_VERSION);
		TCLAP::UnlabeledValueArg<std::string> address("address", "Address to bind to. Default: 8000", false, "8000", &address_constraint, command_line);

		command_line.setExceptionHandling(false);
		command_line.parse(argc, argv);

			ret.address = address.getValue();
	} catch(const TCLAP::ArgException & e) {
		auto arg_id = e.argId();
		if(arg_id == " ")
			arg_id = "undefined argument";
		return std::make_pair(1, std::string(argv[0]) + ": error: parsing arguments failed (" + e.error() + ") for " + arg_id);
	} catch(const TCLAP::ExitException & e) {
		return std::make_pair(e.getExitStatus() ? e.getExitStatus() : 1, std::string{});
	}

	return std::move(ret);
}

bool penerator::operator==(const options & lhs, const options & rhs) {
	return lhs.address == rhs.address;
}

bool penerator::operator!=(const options & lhs, const options & rhs) {
	return !(lhs == rhs);
}
