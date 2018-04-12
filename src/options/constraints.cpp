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


#include "constraints.hpp"
#include "../util.hpp"


#define DEFINE_CONSTRAINT(constraint_name, desc, check_expr)                                                  \
	std::string penerator::constraint_name##_constraint::description() const { return desc; }                   \
                                                                                                              \
	std::string penerator::constraint_name##_constraint::shortID() const { return arg_name; }                   \
                                                                                                              \
	bool penerator::constraint_name##_constraint::check(const std::string & value) const { return check_expr; } \
                                                                                                              \
	penerator::constraint_name##_constraint::constraint_name##_constraint(std::string argname) : arg_name(std::move(argname)) {}


DEFINE_CONSTRAINT(bind_address, "address to bind to in form of [[IP_ADDRESS]:]PORT", verify_bind_address(value))


#undef DEFINE_CONSTRAINT
