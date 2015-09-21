GCC=g++
CFLAGS= -g -I ./include/ -D_LARGEFILE64_SOURCE=1 -DHAVE_HIDDEN -DZ_RANDOM_ACCESS_LIB
LDFLAGS= -L ./lib/i386
TEST_PATH= ./test/
BIN_PATH= ./bin
SRC_PATH= ./src
#LDLIBS := -L./lib/ -llog -liconv -lzip


SRC_FILE_LIST:= $(SRC_PATH)/GoldenDictManager.cpp \
	$(SRC_PATH)/GoldenPathScanner.cpp \
	$(SRC_PATH)/GoldenHtmlHeader.cpp \
	$(SRC_PATH)/GoldenZipTool.cpp \
	$(SRC_PATH)/GoldenIConvTool.cpp \
	$(SRC_PATH)/GoldenGzipHeaderParser.cpp \
	$(SRC_PATH)/GoldenGzipinflate.cpp \
	$(SRC_PATH)/GoldenStandardIO.cpp \
	$(SRC_PATH)/GoldenWordIndexItem.cpp \
	$(SRC_PATH)/StardictDict.cpp \
	$(SRC_PATH)/StardictIdx.cpp \
	$(SRC_PATH)/StardictInfo.cpp \
	$(SRC_PATH)/StardictManager.cpp \
	$(SRC_PATH)/String8.cpp \
	$(SRC_PATH)/Unicode.cpp \

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




test:GoldenDictTest
#memfile libz.a 
#Stardict list_test ref_test avl_test


list_test:
	$(GCC) $(CFLAGS) $(LDFLAGS) $(TEST_PATH)/list_test.cpp -o $(BIN_PATH)/list_test -lz -liconv -lzip
ref_test:
	$(GCC) $(CFLAGS) $(LDFLAGS) $(TEST_PATH)/ref_test.cpp -o $(BIN_PATH)/ref_test -lz -liconv -lzip
avl_test:
	$(GCC) $(CFLAGS) $(LDFLAGS) $(TEST_PATH)/AVLTest.cpp $(SRC_PATH)/StandardIO.cpp $(SRC_PATH)/Unicode.cpp $(SRC_PATH)/String8.cpp -o $(BIN_PATH)/avl_test -lz -liconv -lzip
GoldenDictTest:
	$(GCC) $(CFLAGS) $(LDFLAGS)  $(SRC_FILE_LIST) $(TEST_PATH)/StardictTest.cpp -o $(BIN_PATH)/GoldenDictTest -lz -liconv -lzip
memfile:
	$(GCC) $(CFLAGS) $(LDFLAGS)  $(SRC_FILE_LIST) $(TEST_PATH)/test.c -o $(BIN_PATH)/memfile -lz -liconv -lzip

OBJZ = adler32.o crc32.o deflate.o infback.o inffast.o inflate.o inftrees.o trees.o \
	zutil.o compress.o uncompr.o gzclose.o gzlib.o gzread.o gzwrite.o
$(OBJZ):$(SRC_C_FILE_LIST)
	gcc $(CFLAGS) -c $^
libz.a: $(OBJZ)
	$(AR) $(ARFLAGS) -o ./lib/$@ $^
	rm $(OBJZ)
