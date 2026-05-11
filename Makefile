CC = gcc

SRC = $(wildcard src/*.c)

OUT = build/vidademc

UNAME_S := $(shell uname -s)

CFLAGS = -Iinclude -I/opt/homebrew/include

ifeq ($(UNAME_S), Linux)
    LDFLAGS = -L/usr/local/lib -lraylib -lm -lpthread -ldl -lrt -lX11
endif

ifeq ($(UNAME_S), Darwin)
    LDFLAGS = -L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo
endif

ifeq ($(OS), Windows_NT)
    OUT = build/vidademc.exe
    LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm
endif

all:
	mkdir -p build
	$(CC) $(SRC) $(CFLAGS) -o $(OUT) $(LDFLAGS)

run: all
	./$(OUT)

clean:
	rm -rf build