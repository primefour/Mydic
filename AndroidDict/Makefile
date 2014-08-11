LOCAL_LDLIBS=
LOCAL_LDFLAGS=

TOOLCHAIN_PREFIX=arm-linux-androideabi-
GCC = $(TOOLCHAIN_PREFIX)gcc
GXX = $(TOOLCHAIN_PREFIX)g++
LD       = $(TOOLCHAIN_PREFIX)ld
AR       = $(TOOLCHAIN_PREFIX)ar
STRIP    = $(TOOLCHAIN_PREFIX)strip
OBJCOPY  = $(TOOLCHAIN_PREFIX)objcopy
CXXFLAGS = -fno-exceptions -fno-rtti -Wl,--gc-sections -Wl,-z,nocopyreloc --sysroot="/home/crazyhorse/AndroidDevEn/android-ndk-r9b/platforms/android-19/arch-arm"

libs_in_ldflags := $(filter -l% %.so %.a,$(LOCAL_LDLIBS) $(LOCAL_LDFLAGS))

# Remove the system libraries we know about from the warning, it's ok
# (and actually expected) to link them with -l<name>.
system_libs := \
    android \
    c \
    dl \
    jnigraphics \
    log \
    m \
    m_hard \
    stdc++ \
    z \
    EGL \
    GLESv1_CM \
    GLESv2 \
    GLESv3 \
    OpenSLES \
    OpenMAXAL \
    bcc \
    bcinfo \
    cutils \
    gui \
    RScpp \
    RScpp_static \
    RS \
    ui \
    utils
libs_in_ldflags := $(filter-out $(addprefix -l,$(system_libs)), $(libs_in_ldflags))




GCC := $(GXX)
CFLAGS := $(CXXFLAGS) -g -I ./lib/include -I ./
LDFLAGS := $(LDFLAGS) -L ./lib/lib/ 
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
	
