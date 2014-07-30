GCC=g++
CFLAGS= -g -I ./lib/include -I ./
LDFLAGS= -L ./lib/lib/ 
TEST_PATH= ./test

test:TestFile TestGzip TestStardictInfo TestStardictIdx TestStardictDict
TestFile:*.cpp $(TEST_PATH)/TestFile.cpp *.h 
	$(GCC) $(CFLAGS) $(LDFLAGS) *.cpp $(TEST_PATH)/TestFile.cpp -o $(TEST_PATH)/TestFile -lz
TestGzip:*.cpp $(TEST_PATH)/TestGzip.cpp *.h 
	$(GCC) $(CFLAGS) $(LDFLAGS) *.cpp $(TEST_PATH)/TestGzip.cpp -o $(TEST_PATH)/TestGzip -lz
TestStardictInfo:*.cpp $(TEST_PATH)/TestStardictInfo.cpp *.h 
	$(GCC) $(CFLAGS) $(LDFLAGS) *.cpp $(TEST_PATH)/TestStardictInfo.cpp -o $(TEST_PATH)/TestStardictInfo -lz
TestStardictIdx:*.cpp $(TEST_PATH)/TestStardictIdx.cpp *.h 
	$(GCC) $(CFLAGS) $(LDFLAGS) *.cpp $(TEST_PATH)/TestStardictIdx.cpp -o $(TEST_PATH)/TestStardictIdx -lz
TestStardictDict:*.cpp $(TEST_PATH)/TestStardictDict.cpp *.h 
	$(GCC) $(CFLAGS) $(LDFLAGS) *.cpp $(TEST_PATH)/TestStardictDict.cpp -o $(TEST_PATH)/TestStardictDict -lz

	
