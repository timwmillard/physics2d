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

