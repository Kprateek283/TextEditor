# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g

# Libraries
LIBS = -lfltk -lfltk_images -lX11 -lpthread -lm -lssl -lcrypto

# Source files
SRCS = main.cpp EditorWindow.cpp File_cb.cpp File_spt.cpp Edit.cpp FileReplace.cpp Security.cpp Appearance.cpp StaticFunctions.cpp 

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = my_editor

# Default rule to build the executable
all: $(TARGET)

# Rule to link object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LIBS)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove object files and executable
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
