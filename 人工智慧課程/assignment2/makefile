CC = g++
CFLAGS = -O2 -Wall -Wextra -std=c++17
OBJS = main.o basic.o board.o game.o
EXE = main

all: $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(CFLAGS)

%.o: %.cpp
	$(CC) -c $^ -o $@ $(CFLAGS)

.PHONY: clean
clean:
	${RM} -r $(OBJS) $(EXE)
