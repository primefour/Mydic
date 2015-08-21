GCC = g++

CFLAGS = -I ../include/ -L ../src/ -L../

Csource =$(wildcard *.c)

CPPsource =$(wildcard *.cpp)

object = $(subst .c,.o,$(Csource))

object += $(subst .cpp,.o,$(CPPsource))

string_test:$(Csource) $(CPPsource)
	$(GCC) $(CFLAGS) $+ -liconv -o $@
