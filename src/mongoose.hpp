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


#include "mongoose.h"
#include <memory>
#include <nonstd/variant.hpp>
#include <string>


namespace penerator {
	struct mg_mgr_deleter {
		void operator()(mg_mgr * manager);
	};


	std::unique_ptr<mg_mgr, mg_mgr_deleter> mg_mgr_init(void * userdata);
	std::unique_ptr<mg_mgr, mg_mgr_deleter> mg_mgr_init(void * userdata, mg_mgr_init_opts && opts);

	nonstd::variant<mg_connection *, const char *> mg_bind_or_err(mg_mgr * manager, const char * address, MG_CB(mg_event_handler_t handler, void * user_data));
	nonstd::variant<mg_connection *, const char *> mg_bind_or_err(mg_mgr * manager, const std::string & address,
	                                                              MG_CB(mg_event_handler_t handler, void * user_data));
}
