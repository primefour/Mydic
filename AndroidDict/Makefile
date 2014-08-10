

GCC=g++
CFLAGS= -g -I ./lib/include -I ./
LDFLAGS= -L ./lib/lib/ 
TEST_PATH= ./test
MEM_TEST= memory_test_tool.c 

test:TestFile TestGzip TestStardictInfo TestStardictIdx TestStardictDict mem_test bin_tree_test DirTest TestDictionary
TestFile:*.cpp $(TEST_PATH)/TestFile.cpp *.h 
	$(GCC) $(CFLAGS) $(LDFLAGS) *.cpp $(TEST_PATH)/TestFile.cpp $(MEM_TEST) -o $(TEST_PATH)/TestFile -lz
TestGzip:*.cpp $(TEST_PATH)/TestGzip.cpp *.h 
	$(GCC) $(CFLAGS) $(LDFLAGS) *.cpp $(TEST_PATH)/TestGzip.cpp $(MEM_TEST) -o $(TEST_PATH)/TestGzip -lz
TestStardictInfo:*.cpp $(TEST_PATH)/TestStardictInfo.cpp *.h 
	$(GCC) $(CFLAGS) $(LDFLAGS) *.cpp $(TEST_PATH)/TestStardictInfo.cpp $(MEM_TEST) -o $(TEST_PATH)/TestStardictInfo -lz
TestStardictIdx:*.cpp $(TEST_PATH)/TestStardictIdx.cpp *.h 
	$(GCC) $(CFLAGS) $(LDFLAGS) *.cpp $(TEST_PATH)/TestStardictIdx.cpp $(MEM_TEST)-o $(TEST_PATH)/TestStardictIdx -lz
TestStardictDict:*.cpp $(TEST_PATH)/TestStardictDict.cpp  *.h 
	$(GCC) $(CFLAGS) $(LDFLAGS) *.cpp $(TEST_PATH)/TestStardictDict.cpp $(MEM_TEST)-o $(TEST_PATH)/TestStardictDict -lz
mem_test:*.cpp $(TEST_PATH)/mem_test.c  memory_test_tool.c memory_test_tool.h
	$(GCC) $(CFLAGS) $(LDFLAGS) *.cpp $(MEM_TEST) $(TEST_PATH)/mem_test.c -o $(TEST_PATH)/mem_test -lz
bin_tree_test:*.cpp $(TEST_PATH)/bin_tree_test.cpp  memory_test_tool.c memory_test_tool.h
	$(GCC) $(CFLAGS) $(LDFLAGS) *.cpp $(MEM_TEST) $(TEST_PATH)/bin_tree_test.cpp -o $(TEST_PATH)/bin_tree_test -lz
DirTest:*.cpp $(TEST_PATH)/DirTest.cpp  memory_test_tool.c memory_test_tool.h
	$(GCC) $(CFLAGS) $(LDFLAGS) *.cpp $(MEM_TEST) $(TEST_PATH)/DirTest.cpp -o $(TEST_PATH)/DirTest -lz
TestDictionary:*.cpp $(TEST_PATH)/TestDictionary.cpp  memory_test_tool.c memory_test_tool.h
	$(GCC) $(CFLAGS) $(LDFLAGS) *.cpp $(MEM_TEST) $(TEST_PATH)/TestDictionary.cpp -o $(TEST_PATH)/TestDictionary -lz


	
