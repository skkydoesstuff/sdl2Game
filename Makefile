# Compiler settings
CXX = g++
CXXFLAGS = -Isrc/include -static-libgcc -static-libstdc++
LDFLAGS = -Lsrc/lib
LDLIBS = -lmingw32 -lSDL2main -lSDL2

# Project files
TARGET = main.exe
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

# Main target
all: $(TARGET)

# Linking rule
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(TARGET)

# Compilation rule
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	del /F /Q $(OBJS) $(TARGET)

.PHONY: all clean