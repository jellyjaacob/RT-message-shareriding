#Drake Nguyen + Jacob Le
#Drake: 83197720 cssc1437
#Jacob: 822652578 cssc1431
#CS480-03
#9 April 2022
#Assignment 4

# CXX Make variable for compiler
CXX=g++  
# Make variable for compiler options
#	-std=c++11  C/C++ variant to use, e.g. C++ 2011
#	-g          include information for symbolic debugger e.g. gdb 
CXXFLAGS=-std=c++11 -g

# Rules format:
# target : dependency1 dependency2 ... dependencyN
#     Command to make target, uses default rules if not specified

# First target is the one executed if you just type make
# make target specifies a specific target
# $^ is an example of a special variable.  It substitutes all dependencies

rideshare : producer.o consumer.o broker.o io.o main.o
	$(CXX) $(CXXFLAGS) -o rideshare $^ -lpthread -lrt

producer.o : producer.h producer.cpp

consumer.o : consumer.h consumer.cpp

broker.o : broker.h broker.cpp 

io.o : io.h io.cpp

main.o : ridesharing.h sharedStruct.h main.cpp

clean :
	rm *.o