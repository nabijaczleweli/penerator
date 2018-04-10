# The MIT License (MIT)

# Copyright (c) 2018 nabijaczleweli

# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


include configMakefile


LDDLLS := $(OS_LD_LIBS)
LDAR := $(LNCXXAR) $(foreach l,$(foreach l, ,$(BLDDIR)$(l)),-L$(l)) $(foreach dll,$(LDDLLS),-l$(dll))
INCAR := $(foreach l,mongoose $(foreach l, ,$(l)/include),-isystemext/$(l)) $(foreach l, ,-isystem$(BLDDIR)$(l)/include) -I$(BLDDIR)include
VERAR := $(foreach l,PENERATOR,-D$(l)_VERSION='$($(l)_VERSION)')
SOURCES := $(sort $(wildcard src/*.cpp src/**/*.cpp src/**/**/*.cpp src/**/**/**/*.cpp))
HEADERS := $(sort $(wildcard src/*.hpp src/**/*.hpp src/**/**/*.hpp src/**/**/**/*.hpp))

.PHONY : all clean exe
.SECONDARY :


all : exe

clean :
	rm -rf $(OUTDIR)

exe : $(OUTDIR)penerator$(EXE)


$(OUTDIR)penerator$(EXE) : $(subst $(SRCDIR),$(OBJDIR),$(subst .cpp,$(OBJ),$(SOURCES))) $(BLDDIR)mongoose/mongoose.o
	$(CXX) $(CXXAR) -o$@ $^ $(PIC) $(LDAR)

$(BLDDIR)mongoose/mongoose.o : ext/mongoose/mongoose.c
	@mkdir -p $(dir $@)
	$(CC) $(CCAR) -c -o$@ $^


$(OBJDIR)%$(OBJ) : $(SRCDIR)%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXAR) $(INCAR) $(VERAR) -c -o$@ $^
