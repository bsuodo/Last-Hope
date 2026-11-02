CC = gcc
PKG_CONFIG ?= pkg-config
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic

SOURCES = src/main.c src/Engine.c src/Assets.c src/Object.c src/Renderer.c
SDL_CFLAGS = $(shell $(PKG_CONFIG) --cflags sdl3 sdl3-image 2>/dev/null)
SDL_LIBS = $(shell $(PKG_CONFIG) --libs sdl3 sdl3-image 2>/dev/null)

ifeq ($(OS),Windows_NT)
TARGET = last-hope.exe
else
TARGET = last-hope
endif

.PHONY: all clean check-sdl3

all: $(TARGET)

$(TARGET): $(SOURCES) src/Engine.h src/Assets.h | check-sdl3
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SDL_CFLAGS) $(SOURCES) $(LDFLAGS) $(LDLIBS) $(SDL_LIBS) -o $@

check-sdl3:
	@$(PKG_CONFIG) --exists sdl3 sdl3-image || { echo "SDL3, SDL3_image development files, and pkg-config are required."; exit 1; }

clean:
	$(RM) -f last-hope last-hope.exe
