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


#ifdef _WIN32


#include "tty.hpp"
#include <windows.h>


static std::function<void()> ctrl_c_handler{};


bool penerator::set_ctrl_c_handler(std::function<void()> handler) {
	ctrl_c_handler.swap(handler);

	if(!handler)
		return !SetConsoleCtrlHandler(
		    [](const auto ctrl_type) {
			    if(ctrl_type == CTRL_C_EVENT) {
				    if(ctrl_c_handler)
					    ctrl_c_handler();
				    return TRUE;
			    } else
				    return FALSE;
		    },
		    TRUE);
	else
		return true;
}


#endif
