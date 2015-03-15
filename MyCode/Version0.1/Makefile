GCC=g++
CFLAGS= -g -I ./include/
LDFLAGS= -L ./lib/ 
TEST_PATH= ./test/
BIN_PATH= ./bin/


test:list_test

list_test:
	$(GCC) $(CFLAGS) $(LDFLAGS) $(TEST_PATH)/list_test.cpp -o $(BIN_PATH)/list_test -lz
