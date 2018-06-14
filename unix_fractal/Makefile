## Makefile for fractal
## Modified: 06/14/18

CC			= g++
CC_OPTIONS	= -g -ansi -pedantic -Wall -O
INC 		= settings.h fractal.h micrograph.h Vector_3.h Vector_2.h
INCLUDES	= # -I 
CFLAGS		= $(CC_OPTIONS) $(INCLUDES)

EXE		= fractal
SRC		= 3dstructure.cpp fractal.cpp main.cpp micrograph.cpp orientation.cpp sorensenDf.cpp boxcountDf.cpp Vector_3.cpp Vector_2.cpp
OBJ		= ${SRC:.cpp=.o}

BATCHSRC	= imagejComp.cpp micrograph.cpp sorensenDf.cpp boxcountDf.cpp Vector_2.cpp Vector_3.cpp
BATCHOBJ	= ${BATCHSRC:.cpp=.o}

# Build objects
.SUFFIX: 
.SUFFIX: .c .o .cpp
.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

default: fractal

# Fractal executable
$(EXE):		$(OBJ)	
	$(CC) -o $@ $(CFLAGS) $(OBJ)

# Clean build
clean:
	rm -f a.out core $(OBJ) $(BATCHOBJ)
cleanest:
	rm -f $(EXE) a.out core $(OBJ) $(BATCHOBJ)

# Batch jobs
batchimage:	$(BATCHOBJ)
	$(CC) -o $@ $(CFLAGS) $(BATCHOBJ)

## end of Makefile
