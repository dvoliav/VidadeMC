CC = gcc

CFLAGS = -Wall -Wextra -Iinclude -I/opt/homebrew/include

LDFLAGS = -L/opt/homebrew/lib -lraylib \
-framework OpenGL \
-framework Cocoa \
-framework IOKit \
-framework CoreAudio \
-framework CoreVideo

SRC = \
src/main.c \
src/core/jogo.c \
src/telas/tela_inicio.c

OUT = build/vidademc

all:
	mkdir -p build
	$(CC) $(SRC) $(CFLAGS) -o $(OUT) $(LDFLAGS)

run: all
	./$(OUT)

clean:
	rm -rf build