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
	rm -rf ${OBJDIR}

library: ${OBJECTS}
	${CXX} -shared -Wl,-soname,${LIBRARY_FILE} ${LIBLINKFLAGS} -o ${TOP_DIR}/${LIBRARY_FILE} ${OBJDIR}/*.o 
