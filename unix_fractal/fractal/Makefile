# Fractal makefile
# Modified: Chris Hayes (06/29/18)

CXX = g++
CXX_FLAGS = -std=c++11 -g -Wall -O1

EXE = fracmap
SRC = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRC))

#BATCHSRC = imagejComp.cpp micrograph.cpp sorensenDf.cpp boxcountDf.cpp Vector_2.cpp Vector_3.cpp
#BATCHOBJ = ${BATCHSRC:.cpp=.o}

# Build objects
%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $*.cpp

all: fracmap

# Fractal executable
fracmap: $(OBJS)	
	$(CXX) $(CXX_FLAGS) -o $@ $^

# Clean build
# Remove objects
.PHONY: clean
clean:
	rm -f $(OBJS) $(BATCHOBJ)
# Remove objects and executable
.PHONY: cleanest
cleanest:
	rm -f $(EXE) $(OBJS) $(BATCHOBJ)

# Batch jobs
#batchimage:	$(BATCHOBJ)
	#$(CXX) $(CXX_FLAGS) -o $@ $^

