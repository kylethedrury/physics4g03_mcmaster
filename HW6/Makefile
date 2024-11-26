# Compiler and flags
CXX = g++
CXXFLAGS = -O3 -fopenmp -std=c++11 -Wall -Wextra 

# Source files
SOURCES = main_mp.cc functions_mp.cc
		  
# Object files (replace .cc with .o)
OBJECTS = $(SOURCES:.cc=.o)
	
# Executable name
EXEC = main_mp
	    
# Include paths for header files
INCLUDES = -I.
		   
# Default target
all: $(EXEC)
	
# Link object files to create the executable
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)
								  
# Compile source files to object files
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@
													  
# Clean up build artifacts
clean:
	rm -f $(OBJECTS)
