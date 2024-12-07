CC = gcc
CFLAGS = -Wall -pthread -lncurses

OBJ = main.o mural.o exibicao.o tedax.o coordenador.o utils.o

all: jogo

jogo: $(OBJ)
	$(CC) -o jogo $(OBJ) $(CFLAGS)

%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f *.o jogo
