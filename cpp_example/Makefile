# The libraries to link the fortran
OS := $(shell uname)
ifeq ($(OS), Darwin)
	CLIB += -L/usr/local/Cellar/gcc/8.2.0/lib/gcc/8
endif
CLIB += -lm -lgfortran

HERE := $(shell pwd)

# Run KROME
KROMEPROJ = honly
KROMEFLAGS = -unsafe -o $(HERE)/hj_h_h2.opt -n $(HERE)/hj_h_h2.ntw -project $(KROMEPROJ)

# Build KROME
KROMEBUILDDIR = ../krome/build_$(KROMEPROJ)
KROMEMAKEFLAGS = -f $(HERE)/../krome_custom_Makefile -C $(KROMEBUILDDIR) cinterface gfortran

# Build c++ program
CXXINC = -I$(KROMEBUILDDIR)
CXXFLAGS = -O3 $(INC)

MAINOBJ = main.o
HEADERS = krome.hpp krome_user.hpp
PROGRAM = test
REACTIONSFILE = reactions_verbatim.dat

# Just a note that the default target is the first target. Naming it all is just
# a convention.
all: $(PROGRAM) $(REACTIONS)

$(KROMEBUILDDIR):
	cd ../krome && python2 krome $(KROMEFLAGS)

.PHONY: kromebuild
kromebuild: $(KROMEBUILDDIR)
	make $(KROMEMAKEFLAGS)

# Make C headers C++ compatible by using 'extern "C"'
%.hpp: $(KROMEBUILDDIR)/%.h
	sed 's/extern/extern "C"/g' $< > $@

# Indicate that the C headers are present when krome has been run
$(patsubst %.hpp, $(KROMEBUILDDIR)/%.h, $(HEADERS)): $(KROMEBUILDDIR)

$(REACTIONSFILE): $(KROMEBUILDDIR)
	cp $(KROMEBUILDDIR)/reactions_verbatim.dat $(HERE)

$(MAINOBJ): main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(PROGRAM): $(MAINOBJ) kromebuild
	$(CXX) $(CXXFLAGS) -o $@ $< $(KROMEBUILDDIR)/*.o $(CLIB)

clean:
	rm -r $(KROMEBUILDDIR) $(PROGRAM) $(REACTIONSFILE) $(HEADERS)
