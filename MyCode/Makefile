GCC=g++
CFLAGS= -g -I ./lib/include -I ./
LDFLAGS= -L ./lib/lib/ 
TEST_PATH= ./test

test:TestFile TestGzip
TestFile:*.cpp $(TEST_PATH)/TestFile.cpp *.h 
	$(GCC) $(CFLAGS) $(LDFLAGS) *.cpp $(TEST_PATH)/TestFile.cpp -o $(TEST_PATH)/TestFile -lz
TestGzip:*.cpp $(TEST_PATH)/TestGzip.cpp *.h 
	$(GCC) $(CFLAGS) $(LDFLAGS) *.cpp $(TEST_PATH)/TestGzip.cpp -o $(TEST_PATH)/TestGzip -lz

	
