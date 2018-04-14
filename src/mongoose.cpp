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


void penerator::mg_mgr_deleter::operator()(mg_mgr * manager) {
	mg_mgr_free(manager);
	delete manager;
}

std::unique_ptr<mg_mgr, penerator::mg_mgr_deleter> penerator::mg_mgr_init(void * userdata) {
	auto * manager = new mg_mgr;
	::mg_mgr_init(manager, userdata);
	return std::unique_ptr<mg_mgr, penerator::mg_mgr_deleter>{manager};
}

std::unique_ptr<mg_mgr, penerator::mg_mgr_deleter> penerator::mg_mgr_init(void * userdata, mg_mgr_init_opts && opts) {
	auto * manager = new mg_mgr;
	::mg_mgr_init_opt(manager, userdata, std::move(opts));
	return std::unique_ptr<mg_mgr, penerator::mg_mgr_deleter>{manager};
}

nonstd::variant<mg_connection *, const char *> penerator::mg_bind_or_err(mg_mgr * manager, const char * address,
                                                                         MG_CB(mg_event_handler_t handler, void * user_data)) {
	const char * err = nullptr;
	mg_bind_opts opts{};
	opts.error_string = &err;

	const auto conn = ::mg_bind_opt(manager, address, MG_CB(handler, user_data), opts);

	if(conn)
		return {conn};
	else
		return {err};
}

nonstd::variant<mg_connection *, const char *> penerator::mg_bind_or_err(mg_mgr * manager, const std::string & address,
                                                                         MG_CB(mg_event_handler_t handler, void * user_data)) {
	return mg_bind_or_err(manager, address.c_str(), MG_CB(handler, user_data));
}
