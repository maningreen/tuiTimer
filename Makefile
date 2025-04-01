# SRC
SRC = $(wildcard src/*.c)

# OBJECTS
OBJECTS = $(SRC:src/%.c=$(BUILDDIR)%.o)

# COMPILER
CC = gcc

# flags
LDFLAGS = -lncurses -lm

# target
TARGET = out
BUILDDIR = build/

$(TARGET): $(OBJECTS) $(BUILDDIR)
	$(CC) $(OBJECTS) -o $(BUILDDIR)$(TARGET) $(LDFLAGS)

build/%.o: src/%.c $(BUILDDIR)
	$(CC) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -r $(BUILDDIR)*

run: $(OBJECTS) $(TARGET)
	$(BUILDDIR)$(OUT)
