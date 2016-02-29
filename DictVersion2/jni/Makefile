GCC=g++
CFLAGS= -g -I ./inc/ -I ./lib/i386/include/ -I ./lib/i386/lib/libzip/include/ -I lib/src/rapidjson/include/ -D_LARGEFILE64_SOURCE=1 -DHAVE_HIDDEN -DZ_RANDOM_ACCESS_LIB
LDFLAGS= -L lib/i386/lib/  -L lib/i386/lib/libzip/
TEST_PATH= ./example
BIN_PATH= ./bin
SRC_PATH= ./src
#LDLIBS := -L./lib/ -llog -liconv -lzip


SRC_FILE_LIST:=	$(SRC_PATH)/GoldenZipTool.cpp \
	$(SRC_PATH)/GoldenIConvTool.cpp \
	$(SRC_PATH)/GoldenGzipHeaderParser.cpp \
	$(SRC_PATH)/GoldenGzipinflate.cpp \
	$(SRC_PATH)/GoldenStandardIO.cpp \
	$(SRC_PATH)/String8.cpp \
	$(SRC_PATH)/Unicode.cpp \
	$(SRC_PATH)/AngelDict.cpp \

all: RefTest zZipTest angelWord

REF_TEST_SRC := $(SRC_FILE_LIST)
REF_TEST_SRC += $(TEST_PATH)/AngelRefTest.cpp
RefTest: $(REF_TEST_SRC)
	$(GCC) $(CFLAGS) $(LDFLAGS) $^ -o $(BIN_PATH)/AngelRefTest  -lz -liconv -lzip

ZIP_TEST_SRC := $(SRC_FILE_LIST)
ZIP_TEST_SRC += $(TEST_PATH)/zip_test.cpp
zZipTest: $(ZIP_TEST_SRC)
	$(GCC) $(CFLAGS) $(LDFLAGS) $^ -o $(BIN_PATH)/zZipTest -lz -liconv -lzip

WORD_TEST_SRC := $(SRC_FILE_LIST)
WORD_TEST_SRC += $(TEST_PATH)/AngelWord.cpp
angelWord: $(WORD_TEST_SRC)
	$(GCC) $(CFLAGS) $(LDFLAGS) $^ -o $(BIN_PATH)/angelWord -lz -liconv -lzip

