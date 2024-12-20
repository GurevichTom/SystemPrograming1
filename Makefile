CC=gcc
OBJS=board.o displayGame.o game.o main.o move.o
EXEC=game_2048
DEBUG=	-g
CFLAGS=-std=c99 -Wall -Werror $(DEBUG)

$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $@

board.o: board.c board.h
displayGame.o: displayGame.c displayGame.h
game.o: game.c game.h displayGame.h board.h move.h
main.o: main.c game.h
move.o: move.c move.h

clean:
	rm -f $(OBJS) $(EXEC)
