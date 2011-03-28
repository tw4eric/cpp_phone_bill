MODULENAME = cpp_phone_bill

CC=gcc
CXX=g++
CPPFLAGS+=-ggdb -fPIC -rdynamic
#CPPFLAGS+=-O0 -pg -fprofile-arcs -ftest-coverage

INCLUDES=-I$(TOP_DIR)/include

LIBLINKFLAGS=-L$(TOP_DIR)

OBJDIR ?= $(TOP_DIR)/.obj
LIBRARY_FILE = lib$(MODULENAME).so

.SUFFIXES: .hh .cc .o

PHONY: $(OBJDIR) all

.cc.o: $(OBJDIR)
	${CXX} ${INCLUDES} ${CPPFLAGS} -c -o $@ $< && cp $@ ${OBJDIR}/

$(OBJDIR):
	if [ ! -z $(OBJDIR) -a ! -d $(OBJDIR) ]; then mkdir -p $(OBJDIR); fi
