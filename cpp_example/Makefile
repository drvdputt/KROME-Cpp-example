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

# Just a note that the default target is the first target. Naming it all is just
# a convention.
all: $(PROGRAM) reactions_verbatim.dat

# Run krome, if necessary
$(KROME_OUTPUT):
	cd ../krome && python2 krome -o $(HERE)/hj_h_h2.opt -n $(HERE)/hj_h_h2.ntw -project $(PROJ)

# Build krome by running make
.PHONY: kromebuild
kromebuild: $(KROME_OUTPUT)
	make -f $(HERE)/../krome_custom_Makefile -C $(KROME_OUTPUT) cinterface gfortran

# Make headers C++ compatible and put them here
%.hpp: $(KROME_OUTPUT)/%.h
	sed 's/extern/extern "C"/g' $< > $@

# Indicate that the C headers are present when krome has been run
$(patsubst %.hpp, $(KROME_OUTPUT)/%.h, $(HEADERS)): $(KROME_OUTPUT)

reactions_verbatim.dat: $(KROME_OUTPUT)
	cp $(KROME_OUTPUT)/reactions_verbatim.dat .

$(MAINOBJ): main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(PROGRAM): $(MAINOBJ) kromebuild
	$(CXX) $(CXXFLAGS) -o $@ $< $(KROME_OUTPUT)/*.o $(CLIB)

clean:
	rm -r $(KROME_OUTPUT) $(PROGRAM) reactions_verbatim.dat $(HEADERS)
