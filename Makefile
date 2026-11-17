CXX = g++
CXXFLAGS = -std=c++17 -Iheaders

TARGET = simote

SOURCES = main.cpp \
          $(wildcard controllers/*.cpp) \
          $(wildcard data/*.cpp) \
          $(wildcard utils/*.cpp)

all:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)