GCC = gcc

CFLAGS = -I ../include/ -L ../src/ -liconv

source =$(wildcard *.c)

object = $(subst .c,.o,$(source))

string_test:$(source)
	$(GCC) $(CFLAGS) $+ -o $@
