CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	CFLAGS += -I/opt/homebrew/include

	LDFLAGS = -L/opt/homebrew/lib -lraylib \
	-framework OpenGL \
	-framework Cocoa \
	-framework IOKit \
	-framework CoreAudio \
	-framework CoreVideo

else
	LDFLAGS = -lraylib -lm -lpthread -ldl -lrt -lX11
endif

SRC = \
src/main.c \
src/core/jogo.c \
src/ui/botao.c \
src/telas/tela_inicio.c \
src/telas/tela_save.c \
src/telas/tela_criar_mc.c \
src/telas/tela_menu.c \
src/telas/tela_acoes.c \
src/telas/tela_minigame.c \
src/minigames/show.c

OUT = build/vidademc

all:
	mkdir -p build
	$(CC) $(SRC) $(CFLAGS) -o $(OUT) $(LDFLAGS)

run: all
	./$(OUT)

clean:
	rm -rf build