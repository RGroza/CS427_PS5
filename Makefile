CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

TARGET = kalah
SRCS = main.cpp tools.cpp Board.cpp Pit.cpp Kalah.cpp Game.cpp Snapshot.cpp Startup.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp Board.hpp Pit.hpp Player.hpp tools.hpp Kalah.hpp Game.hpp Snapshot.hpp Startup.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
