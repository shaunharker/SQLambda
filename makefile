CXXFLAGS := -std=c++11 -O3 -DNDEBUG -I./include
LDLIBS := -lsqlite3

# List of targets
all: example
