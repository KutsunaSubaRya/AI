CC = g++
CFLAGS = -O2 -std=c++17
OBJS = main.o ./gameLib/basic.o ./gameLib/board.o ./gameLib/game.o
EXE = main

all: $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(CFLAGS)

%.o: %.cpp
	$(CC) -c $^ -o $@ $(CFLAGS)

.PHONY: clean
clean:
	${RM} -r $(OBJS) $(EXE)