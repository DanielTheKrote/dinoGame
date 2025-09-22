CC=gcc
CFLAGS=-Wall -Werror -std=c99
LDFLAGS=-lncurses
SRCDIR=src
OBJDIR=objs
EXE=dino

SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJECTS=$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	rm $(EXE) -r $(OBJDIR)
