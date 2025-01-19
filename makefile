CC = gcc
CFLAGS = -c -Wall -I$(INCDIR)
TOPDIR = $(PWD)
SRCDIR = $(TOPDIR)/src/
INCDIR = $(TOPDIR)/inc/
OBJDIR = $(TOPDIR)/obj/

SRCLIST = $(wildcard $(SRCDIR)*.c)
OBJTEMP = $(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRCLIST))
OBJ = $(OBJTEMP)
BINDIR = $(TOPDIR)/out/
BIN = $(BINDIR)test

all: CHECKDIR test
CHECKDIR:
	mkdir -p $(OBJDIR) $(BINDIR)

test: $(BIN)
$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $@
$(OBJDIR)%.o: $(SRCDIR)%.c 
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(BINDIR)