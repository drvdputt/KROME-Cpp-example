CXX=g++

HERE=$(shell pwd)
PROJ=honly
KROME_OUTPUT=../krome/build_$(PROJ)

INC=-I$(KROME_OUTPUT)
CXXFLAGS=-O3 $(INC)
CLIB=-lm -lgfortran

MAINOBJ=main.o
HEADERS=krome.hpp krome_user.hpp
PROGRAM=test

all: $(PROGRAM) reactions_verbatim.dat

.PHONY: kromeobjs
kromeobjs:
	cd ../krome && python2 krome -o $(HERE)/hj_h_h2.opt -n $(HERE)/hj_h_h2.ntw -project $(PROJ)
	cp ../krome_custom_Makefile $(KROME_OUTPUT)
	make -f krome_custom_Makefile -C $(KROME_OUTPUT) cinterface gfortran

# Make headers C++ compatible
%.hpp: $(KROME_OUTPUT)/%.h kromeobjs
	sed 's/extern/extern "C"/g' $< > $@

# Rule for the C headers
CHD = $(patsubst %.hpp, $(KROME_OUTPUT)/%.h, $(HEADERS))
$(info $(CHD))
$(CHD): kromeobjs

reactions_verbatim.dat: kromeobjs
	cp $(KROME_OUTPUT)/reactions_verbatim.dat .

$(MAINOBJ): main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(PROGRAM): $(MAINOBJ) kromeobjs
	$(CXX) $(CXXFLAGS) -o $@ $< $(KROME_OUTPUT)/*.o $(CLIB)
