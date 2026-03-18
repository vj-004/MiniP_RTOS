# MiniP_RTOS Makefile
CXX = g++
CXXFLAGS = -std=c++23 -Wall -I. -Ikernal -Ischeduler -Itask -mconsole
SRCS = main.cpp kernal/rtos.cpp scheduler/scheduler.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = rtos.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(CXXFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q $(OBJS) $(TARGET) 2>nul