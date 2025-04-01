# SRC
SRC = $(wildcard src/*.c)

# OBJECTS
OBJECTS = $(SRC:src/%.c=$(BUILDDIR)%.o)

# COMPILER
CC = gcc

# the standard for that there c
STD = c99

# flags
LDFLAGS = -lncurses -lm

# target
TARGET = out
BUILDDIR = build/

$(TARGET): $(OBJECTS) $(BUILDDIR)
	$(CC) $(OBJECTS) -o $(BUILDDIR)$(TARGET) $(LDFLAGS)

build/%.o: src/%.c $(BUILDDIR)
	$(CC) -std=$(STD) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -r $(BUILDDIR)*

run: $(OBJECTS) $(TARGET)
	$(BUILDDIR)$(OUT)
