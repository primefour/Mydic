GCC=g++
CFLAGS= -I ./lib/include
LDFLAGS=-L ./lib/lib/

all:
	$(GCC) $(CFLAGS) *.c

test:TestFile
	$(GCC) $(CFLAGS) *.cpp ./test/*.cpp -o TestFile
	
