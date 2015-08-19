GCC = gcc

CFLAGS = -I ../include/ -L ../src/ -L../

source =$(wildcard *.c)

object = $(subst .c,.o,$(source))

string_test:$(source)
	$(GCC) $(CFLAGS) $+ -lhello -liconv -o $@
