export TOP_DIR=..
OBJDIR=.obj
include $(TOP_DIR)/global.mak
SOURCE_FILES_CPP=$(shell ls */*.cc)
OBJECTS_CPP=$(SOURCE_FILES_CPP:.cc=.o)

OBJECTS = $(OBJECTS_CPP)

${OBJECTS}: ${OBJDIR}

all: library

clean:
	rm -f $(OBJECTS)

library: ${OBJECTS}
	${CXX} -fPIC -shared ${LIBLINKFLAGS} -o ${LIBRARY_FILE} ${OBJDIR}/*.o 
