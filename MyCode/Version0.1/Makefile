GCC=g++
CFLAGS= -g -I ./include/
LDFLAGS= -L ./lib/ 
TEST_PATH= ./test/
BIN_PATH= ./bin
SRC_PATH= ./src


test:list_test ref_test avl_test

list_test:
	$(GCC) $(CFLAGS) $(LDFLAGS) $(TEST_PATH)/list_test.cpp -o $(BIN_PATH)/list_test -lz
ref_test:
	$(GCC) $(CFLAGS) $(LDFLAGS) $(TEST_PATH)/ref_test.cpp -o $(BIN_PATH)/ref_test -lz
avl_test:
	$(GCC) $(CFLAGS) $(LDFLAGS) $(TEST_PATH)/AVLTest.cpp $(SRC_PATH)/StandardIO.cpp $(SRC_PATH)/Unicode.cpp $(SRC_PATH)/String8.cpp -o $(BIN_PATH)/avl_test -lz
