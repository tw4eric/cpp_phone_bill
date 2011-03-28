export TOP_DIR = $(shell pwd)

include global.mak

SUB_DIRS = src test

all: subdirmake

subdirmake:
	@for d in $(SUB_DIRS); do cd $$d && make all && cd -; done

test: all
	cd test && make test

clean:
	@for d in $(SUB_DIRS); do cd $$d && make $@ && cd -; done
