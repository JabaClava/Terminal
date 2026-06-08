CXX = g++
CXXFLAGS = -std=c++20 -Wall -g

TARGET = term

SRCS = main.cpp Terminal.cpp Directory.cpp Entry.cpp MultiLineFile.cpp \
PostponedFile.cpp SingleLineFile.cpp

OBJS = $(SRCS:.cpp=.o)

HEADERS = Terminal.h Directory.h Entry.h MultiLineFile.h PostponedFile.h \
SingleLineFile.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean