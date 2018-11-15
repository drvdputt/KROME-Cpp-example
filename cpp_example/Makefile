CXX=g++

KROME_OUTPUT=../krome/build_honly

INC=-I$(KROME_OUTPUT)
CXXFLAGS=-O3 $(INC)
CLIB=-lm -lgfortran

MAINOBJ=main.o
PROGRAM=test

all: $(PROGRAM) reactions_verbatim.dat

reactions_verbatim.dat:
	cp $(KROME_OUTPUT)/reactions_verbatim.dat .

.PHONY: kromeobjs

$(PROGRAM): $(MAINOBJ) kromeobjs
	$(CXX) $(CXXFLAGS) -o $@ $< $(KROME_OUTPUT)/*.o $(CLIB)

$(MAINOBJ): main.cpp krome.hpp krome_user.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Make headers c++ compatible
%.hpp: $(KROME_OUTPUT)/%.h
	sed 's/extern/extern "C"/g' $^ > $@

kromeobjs:
	cp ../krome_custom_Makefile $(KROME_OUTPUT)
	make -f krome_custom_Makefile -C $(KROME_OUTPUT) cinterface gfortran



