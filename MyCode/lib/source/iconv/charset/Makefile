GCC=gcc
CXXFLAGS += -c
CFLAGS += -c
SOURCE = $(wildcard *.c)
OBJECT=$(subst .c,.o,$(SOURCE)) 


all:$(OBJECT)
%.o: %.c  %.h
	$(GCC) $(CFLAGS)  $< 

clean:
	rm -rf *.o
