#makefile

CC = g++

UCFLAGS = -O3 -Wall -gstabs+ -std=c++0x

RUCFLAGS := $(shell root-config --cflags) -I./include/ -I/home/llr/cms/kovac/CMS/Analysis/SpinParity/Validation/CMSSW_5_3_9/src/ -I/cvmfs/cms.cern.ch/slc5_amd64_gcc462/lcg/roofit/5.32.03-cms16/include/

LIBS := $(shell root-config --libs) -lTreePlayer -lZZMatrixElementMELA -L/home/llr/cms/kovac/CMS/Analysis/SpinParity/Validation/CMSSW_5_3_9/lib/slc5_amd64_gcc462/

GLIBS := $(shell root-config --glibs)

VPATH = ./src/

SRCPP = Main.cpp\
        addProbToTree.cpp\
         
OBJCPP = $(patsubst %.cpp,obj/%.o,$(SRCPP))

all : run

obj/%.o : %.cpp
	@echo ">> compiling $*"
	@mkdir -p obj/
	@$(CC) -c $< $(UCFLAGS) $(RUCFLAGS) -o $@

run : $(OBJCPP)
	@echo ">> linking..."
	@$(CC) $^ $(ACLIBS) $(LIBS) $(GLIBS)  -o $@

clean:
	@echo ">> cleaning objects and executable"
	@rm  -f obj/*.o
	@rm -f run
