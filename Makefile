CXX	= g++
SOURCES	= $(wildcard *.cpp)
HEADERS = $(wildcard *.hpp)

#------------- Changes below ---------------
CXXFLAGS = -Wall -g
EXEC = mondrian.out
#------------- Changes above ---------------
all: $(EXEC) run

$(EXEC): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(HEADERS) $(SOURCES) -o $(EXEC)

run: $(EXEC)
	./$(EXEC)

clean:
	rm $(EXEC)

.PHONY: clean