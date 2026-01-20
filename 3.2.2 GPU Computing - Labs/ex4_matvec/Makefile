TARGET= matvec
OBJS	= main.o matvec.o matvec_offload.o alloc2d.o 

OPT	= -g -fast -Msafeptr -Minfo -acc -mp=gpu -gpu=cc90 -gpu=lineinfo -cuda -mp=noautopar
ISA	= 
PARA	= -fopenmp
CC	= nvc

CCC	= nvc++
CXX	= nvc++

CFLAGS	= $(OPT) $(ISA) $(PARA) $(XOPT)
CXXFLAGS	= $(OPT) $(ISA) $(PARA) $(XOPT) 

F90C  	= gfortran
LIBS	= -lblas -cudalib=cublas


all: $(TARGET)

$(TARGET): $(OBJS) 
	$(CCC) $(CXXFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	@/bin/rm -f *.o core

realclean: clean
	@rm -f $(TARGET)

# dependencies
#
main.o  : main.cpp matvec.h matvec_offload.h
matvec.o: matvec.h matvec.cpp
matvec_offload.o: matvec_offload.h matvec_offload.cpp
alloc2d.o: alloc2d.h alloc2d.cpp
