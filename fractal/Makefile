# Fractal makefile
# Modified: Chris Hayes (06/29/18)

CXX = g++
CXXFLAGS = -std=c++11 -pedantic -g -Wall -O1 -DBOOST_ALL_DYN_LINK -I/usr/local/Cellar/boost/1.67.0_1/include
LDFLAGS = -L/usr/local/Cellar/boost/1.67.0_1/lib
# LIBS = -lboost_log -lboost_log_setup -lboost_system -lboost_filesystem 
LIBS = -lboost_filesystem -lboost_system -lboost_date_time -lboost_thread-mt -lboost_regex -lboost_log-mt -lboost_log_setup

EXE = fracmap
SRC = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRC))

#BATCHSRC = imagejComp.cpp micrograph.cpp sorensenDf.cpp boxcountDf.cpp Vector_2.cpp Vector_3.cpp
#BATCHOBJ = ${BATCHSRC:.cpp=.o}

# Build objects
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $*.cpp

all: fracmap

# Fractal executable
fracmap: $(OBJS)	
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

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

