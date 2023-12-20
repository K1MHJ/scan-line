.PHONY: all run
CC=clang
CPP:=clang++
AR=ar
RANLIB=ranlib
LD := clang++
CFLAGS= -g -Wall
CPPFLAGS= -g -Wall -std=c++20
SRCDIR := ./
OBJDIR := ./obj
BINDIR := ./bin
INCLUDE := -I. -I/opt/homebrew/include/ -I/usr/include/ -I/usr/local/include/
INCLUDE := $(INCLUDE)
DEPS=
LIBS=-lm
DEFINES:= 
PROGRAM = demo
BINFILE=$(PROGRAM:%=$(BINDIR)/%)

all: $(BINFILE)

run:
	$(BINFILE)

$(BINFILE): $(SRCDIR)/main.cpp
	mkdir -p $(@D)
	$(CPP) $(CFLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)

clean :
	rm -rf $(BINDIR) $(OBJDIR)
