.PHONY: all clean run
# change application name here (executable output name)
TARGET=dodgeball

# compiler
CC=clang
# linker
LD=clang
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall

# CFLAGS=$(DEBUG) $(OPT) $(WARN)

## Statically linked build
# Need to build raylib from source first

# raylib
CFLAGS += -Ilib/raylib-5.0/src
LDFLAGS += -Llib/raylib-5.0/src -lraylib
FRAMEWORKS = -framework IOKit -framework Cocoa

all: $(TARGET)

$(TARGET) : main.o
	$(LD) -o $(TARGET) $< $(FRAMEWORKS) $(LDFLAGS)

main.o: src/main.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

release: main.o
	$(LD) -o $(TARGET) $< $(FRAMEWORKS) $(LDFLAGS)
	cp $(TARGET) release/$(TARGET).app/Contents/MacOS/


#emcc -o game.html game.c -Os -Wall ./path-to/libraylib.a -I. -Ipath-to-raylib-h -L. -Lpath-to-libraylib-a -s USE_GLFW=3 --shell-file path-to/shell.html -DPLATFORM_WEB
web:
	emcc -o game.html src/main.c -Os -Wall \
		./lib/raylib-5.0/src/libraylib.a \
		-Ilib/raylib-5.0/src \
		-Llib/raylib-5.0/src \
		-s USE_GLFW=3 \
		-DPLATFORM_WEB

# all: $(TARGET)

# $(TARGET): %.o
# 	$(LD) -o $(TARGET) $< $(LDFLAGS)

# %.o: src/%.c
# 	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

raylib:
	cd lib/raylib-5.0/src
	make

run:
	./$(TARGET)

clean:
	rm -f *.o $(TARGET) release/$(TARGET).app/Contents/MacOS/$(TARGET)

