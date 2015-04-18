GCC=g++
CFLAGS= -g -I ./include/ -D_LARGEFILE64_SOURCE=1 -DHAVE_HIDDEN -DZ_RANDOM_ACCESS_LIB
LDFLAGS= -L ./lib/ 
TEST_PATH= ./test/
BIN_PATH= ./bin
SRC_PATH= ./src

SRC_FILE_LIST:= $(SRC_PATH)/String8.cpp \
	$(SRC_PATH)/StandardIO.cpp \
	$(SRC_PATH)/Unicode.cpp \
	$(SRC_PATH)/StardictInfo.cpp \
	$(SRC_PATH)/StardictMain.cpp \
	$(SRC_PATH)/StardictIdx.cpp \
	$(SRC_PATH)/GzipHeaderParser.cpp \
	$(SRC_PATH)/GzipDeflate.cpp \
	$(SRC_PATH)/StardictDict.cpp \

SRC_C_FILE_LIST := src/adler32.c \
	src/compress.c \
	src/crc32.c \
	src/deflate.c \
	src/gzclose.c \
	src/gzlib.c \
	src/gzread.c \
	src/gzwrite.c \
	src/infback.c \
	src/inffast.c \
	src/inflate.c \
	src/inftrees.c \
	src/trees.c \
	src/uncompr.c \
	src/zutil.c \




test: memfile libz.a
#Stardict list_test ref_test avl_test


list_test:
	$(GCC) $(CFLAGS) $(LDFLAGS) $(TEST_PATH)/list_test.cpp -o $(BIN_PATH)/list_test -lz
ref_test:
	$(GCC) $(CFLAGS) $(LDFLAGS) $(TEST_PATH)/ref_test.cpp -o $(BIN_PATH)/ref_test -lz
avl_test:
	$(GCC) $(CFLAGS) $(LDFLAGS) $(TEST_PATH)/AVLTest.cpp $(SRC_PATH)/StandardIO.cpp $(SRC_PATH)/Unicode.cpp $(SRC_PATH)/String8.cpp -o $(BIN_PATH)/avl_test -lz
Stardict:
	$(GCC) $(CFLAGS) $(LDFLAGS)  $(SRC_FILE_LIST) -o $(BIN_PATH)/Stardict -lz
memfile:
	$(GCC) $(CFLAGS) $(LDFLAGS)  $(SRC_FILE_LIST) $(TEST_PATH)/test.c -o $(BIN_PATH)/memfile -lz

OBJZ = adler32.o crc32.o deflate.o infback.o inffast.o inflate.o inftrees.o trees.o \
	zutil.o compress.o uncompr.o gzclose.o gzlib.o gzread.o gzwrite.o
$(OBJZ):$(SRC_C_FILE_LIST)
	gcc $(CFLAGS) -c $^
libz.a: $(OBJZ)
	$(AR) $(ARFLAGS) -o ./lib/$@ $^
	rm $(OBJZ)
