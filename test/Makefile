TOP_DIR = ..
OBJDIR=./.obj

LD_LIBRARY_PATH=`gtest-config --libdir`:`gmock-config --libdir`:..

include ${TOP_DIR}/global.mak
LIBLINKFLAGS+=`gtest-config --cxxflags`
LIBLINKFLAGS+=`gtest-config --ldflags`
LIBLINKFLAGS+=`gtest-config --libs`
LIBLINKFLAGS+=`gmock-config --cxxflags`
LIBLINKFLAGS+=`gmock-config --ldflags`
LIBLINKFLAGS+=`gmock-config --libs`
LIBLINKFLAGS+=-L${TOP_DIR} -l${MODULENAME}
INCLUDES+=`gtest-config --cppflags` `gmock-config --cppflags`

SOURCES_CPP = $(shell ls */*.cc)
SUB_DIRS = #extra
OBJECTS=$(SOURCES_CPP:.cc=.o)

${OBJECTS}:${OBJDIR}

EXE=cpp_phone_bill_tests

${EXE}:${OBJECTS}
	${CXX} ${LIBLINKFLAGS} ${OBJECTS} -o $@

all: ${EXE}

test: all
	export LD_LIBRARY_PATH=${LD_LIBRARY_PATH} && ./${EXE}

clean:
	rm -f ${EXES} ${OBJECTS}
	rm -rf ${OBJDIR}
