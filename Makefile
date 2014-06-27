GCC=g++
CFLAGS= -I ./lib/include -I ./
LDFLAGS=-L ./lib/lib/
TEST_PATH=./test



test:TestFile

TestFile:*.cpp $(TEST_PATH)/*.cpp *.h *.c 
	$(GCC) $(CFLAGS) $(LDFLAGS) *.cpp $(TEST_PATH)/*.cpp -o $(TEST_PATH)/TestFile

	
