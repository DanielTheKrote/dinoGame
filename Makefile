CC=gcc
SRCDIR=src
OBJDIR=objs
INCLUDEDIR=include
EXE=dino

CFLAGS=-Wall -Werror -std=gnu99 -I$(INCLUDEDIR) -MMD -MP
LDFLAGS=-lncurses

SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJECTS=$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

DEP=$(OBJECTS:.o=.d)

all: $(EXE)
	./$(EXE)

$(EXE): $(OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -c $< $(CFLAGS) -o $@ 

-include $(DEP)

$(OBJDIR):
	-mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	-rm $(EXE) -r $(OBJDIR)
