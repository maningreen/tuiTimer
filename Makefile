# SRC
SRC = $(wildcard src/*.c)

# OBJECTS
OBJECTS = $(SRC:src/%.c=$(BUILDDIR)%.o)

# COMPILER
CC = gcc

# flags
LDFLAGS = -lncurses -lm

# target
TARGET = build/out
BUILDDIR = build/

$(TARGET): $(OBJECTS) $(BUILDDIR)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

build/%.o: src/%.c $(BUILDDIR)
	$(CC) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -r $(BUILDDIR)*

run: $(TARGET)
	$(BUILDDIR)$(OUT)
