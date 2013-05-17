#Generic Makefile for the a ROOT usable library

SRCSUF = cc
OBJSUF = o
EXESUF = 
CXX = g++
LD = g++
CXXFLAGS = -O -O2 -fPIC -std=c++0x -Wall
LDFLAGS := $(shell root-config --ldflags)
SOFLAGS = -shared

#ROOT libraries and headers to include
ROOTLIB := $(shell root-config --glibs)
INC := $(shell root-config --cflags)

#Class source files
SRC := $(wildcard *.$(SRCSUF))
OBJ := $(SRC:.$(SRCSUF)=.$(OBJSUF))

#Executable source files (must contain main())
EXESRC := $(wildcard main/*.$(SRCSUF))
EXEOBJ := $(EXESRC:.$(SRCSUF)=.$(OBJSUF))
EXE := $(patsubst main/%.$(OBJSUF), %$(EXESUF), $(wildcard main/*.$(OBJSUF)))

#Library stuff - dictionary and lib file
DICT := $(patsubst %_LinkDef.h, %Dict.cc, $(wildcard *_LinkDef.h))
LIB = PACSSlib.so

#Put together the whole library
#lib: $(DICT) $(OBJ) dynamiclib
all: $(DICT) $(OBJ) $(EXEOBJ) dynamiclib $(EXE)

#First, generate the dictionary
%Dict.$(SRCSUF): %.hh %_LinkDef.h
	rootcint -f $@ -c $(INC) $^

#Compile the source files
#g++ -c <flags> <includes> <object files> -o <source files> 
%.$(OBJSUF): %.$(SRCSUF)
	@echo Compiling source files into object files...
	$(CXX) -c -g $(CXXFLAGS) $(INC) $< -o $@

#Link the executables
#g++ <flags> <exe to make> -o <object file> <libs to include>
%$(EXESUF): main/%.$(OBJSUF)
	@echo Linking executable...
	$(LD) $(LDFLAGS) $< -o $@ $(LIB) $(ROOTLIB)

#Link it together
dynamiclib: $(OBJ) $(DICT)
	@echo Generating library $(LIB)...
	$(LD) $(SOFLAGS) $(LDFLAGS) $(OBJ) -o $(LIB) $(ROOTLIB)
	cp $(LIB) $(HOME)/usr/lib/

.PHONY: clean

clean:
	rm $(EXEOBJ) $(OBJ) $(EXE) $(LIB) $(DICT)
	rm $(HOME)/usr/lib/$(LIB)
	rm *.*~
