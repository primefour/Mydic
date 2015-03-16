GCC=g++
CFLAGS= -g -I ./include/
LDFLAGS= -L ./lib/ 
TEST_PATH= ./test/
BIN_PATH= ./bin/


test:list_test ref_test

list_test:
	$(GCC) $(CFLAGS) $(LDFLAGS) $(TEST_PATH)/list_test.cpp -o $(BIN_PATH)/list_test -lz
ref_test:
	$(GCC) $(CFLAGS) $(LDFLAGS) $(TEST_PATH)/ref_test.cpp -o $(BIN_PATH)/ref_test -lz
