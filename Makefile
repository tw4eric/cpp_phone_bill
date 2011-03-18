export TOP_DIR = $(shell pwd)

include global.mak

SUB_DIRS = src test
SUB_DIRS_WITH_TEST = ${SUB_DIRS}

all: $(OBJDIR) subdirmake

subdirmake:
	@for d in $(SUB_DIRS); do cd $$d && make all && cd -; done

test: all
	cd test && make all

clean:
	@for d in $(SUB_DIRS_WITH_TEST); do cd $$d && make $@ && cd -; done
	rm -f $(LIBRARY_FILE) $(OBJDIR)/*.o
