/*
 * Copyright (C) 2005 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "String8.h"
#include <ctype.h>
#include <stdio.h>
#include "GoldenDictLog.h"

/*
 * Functions outside android is below the namespace android, since they use
 * functions and constants in android namespace.
 */

// ---------------------------------------------------------------------------

// Separator used by resource paths. This is not platform dependent contrary
// to OS_PATH_SEPARATOR.
#define OS_PATH_SEPARATOR '/'
#define RES_PATH_SEPARATOR '/'

static char* gEmptyString = NULL;

static inline char* getEmptyString()
{
    return gEmptyString;
}

void terminate_string8()
{
    gEmptyString = NULL;
}

// ---------------------------------------------------------------------------

static char* allocFromUTF8(const char* in, size_t len)
{
    if (len > 0) {
        char *buf = new char[len + 1];
        if (buf != NULL) {
            char* str = buf;
            memcpy(str, in, len);
            str[len] = 0;
            return str;
        }
        return NULL;
    }
    return getEmptyString();
}


static char* allocFromUTF16(const char16_t* in, size_t len)
{
    if (len == 0) return getEmptyString();

    const ssize_t bytes = utf16_to_utf8_length(in, len);
    if (bytes < 0) {
        return getEmptyString();
    }
    char* buf = new char[bytes +1]; 
    if (!buf) {
        return getEmptyString();
    }

    char* str = (char*)buf;
    utf16_to_utf8(in, len, str);
    return str;
}

static char* allocFromUTF32(const char32_t* in, size_t len)
{
    if (len == 0) {
        return getEmptyString();
    }

    const ssize_t bytes = utf32_to_utf8_length(in, len);
    if (bytes < 0) {
        return getEmptyString();
    }

    char* buf = new char[bytes +1]; 
    if (!buf) {
        return getEmptyString();
    }

    char* str = (char*) buf;
    utf32_to_utf8(in, len, str);

    return str;
}

// ---------------------------------------------------------------------------

String8::String8()
    : mString(getEmptyString())
{
}

String8::String8(StaticLinkage)
    : mString(0)
{
    // this constructor is used when we can't rely on the static-initializers
    // having run. In this case we always allocate an empty string. It's less
    // efficient than using getEmptyString(), but we assume it's uncommon.

    char* data = new char[1]; 
    data[0] = 0;
    mString = data;
}

String8::String8(const String8& o)
{
    if(!o.isEmpty()){
        mString = allocFromUTF8(o.mString, strlen(o.mString));
    }else{
        mString = getEmptyString();
    }
}

String8::String8(const char* o)
{
    if(o != NULL){
        mString = allocFromUTF8(o, strlen(o));
    }else{
        mString = getEmptyString();
    }
}

String8::String8(const char* o, size_t len)
    : mString(allocFromUTF8(o, len))
{
    if (mString == NULL) {
        mString = getEmptyString();
    }
}


String8::~String8()
{
    if(mString != NULL){
        delete[] mString;
    }
    mString = NULL;
}

String8 String8::format(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    String8 result(formatV(fmt, args));

    va_end(args);
    return result;
}

String8 String8::formatV(const char* fmt, va_list args)
{
    String8 result;
    result.appendFormatV(fmt, args);
    return result;
}


void String8::setTo(const String8& other)
{
    setTo(other.mString);
}

int String8::setTo(const char* other)
{
    if(mString != NULL){
        delete[] mString; 
        mString = NULL;
    }
    if(other == NULL){
        mString = getEmptyString();
        return 0;
    }else{
        const char *newString = allocFromUTF8(other, strlen(other));
        mString = newString;
        if (mString) {
            return 0;
        } else {
            return -1;
        }
    }
}

int String8::setTo(const char* other, size_t len)
{
    if(mString != NULL){
        delete[] mString; 
        mString = NULL;
    }
    if(other == NULL){
        mString = getEmptyString();
        return 0;
    }else{
        const char *newString = allocFromUTF8(other, len);
        mString = newString;
        if (mString) {
            return 0;
        } else {
            return -1;
        }
    }
}

int String8::append(const String8& other)
{
    const size_t otherLen = other.bytes();
    if (bytes() == 0) {
        setTo(other);
        return 0;
    } else if (otherLen == 0) {
        return 0;
    }

    return real_append(other.string(), otherLen);
}


int String8::append(const char* other)
{
    return append(other, strlen(other));
}


int String8::append(const char* other, size_t otherLen)
{
    if (bytes() == 0) {
        return setTo(other, otherLen);
    } else if (otherLen == 0) {
        return 0;
    }

    return real_append(other, otherLen);
}

int String8::appendFormat(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    int result = appendFormatV(fmt, args);

    va_end(args);
    return result;
}

int String8::appendFormatV(const char* fmt, va_list args)
{
    int n, result = 0;
    va_list tmp_args;

    /* args is undefined after vsnprintf.
     * So we need a copy here to avoid the
     * second vsnprintf access undefined args.
     */
    va_copy(tmp_args, args);
    n = vsnprintf(NULL, 0, fmt, tmp_args);
    va_end(tmp_args);

    if (n != 0) {
        size_t oldLength = length();
        char *buf = new char[oldLength + n + 1];
        if (buf) {
            if(mString != NULL){
                memcpy(buf,mString,size());
                delete[] mString;
            }
            mString = buf;
            vsnprintf(buf + oldLength, n + 1, fmt, args);
        } else {
            result = -1;
        }
    }
    return result;
}

int String8::real_append(const char* other, size_t otherLen)
{
    const size_t myLen = bytes();
    
    char * buf = new char[myLen + otherLen + 1];
    if (buf) {
        char* str = (char*)buf;
        if(mString != NULL){
            memcpy(str,mString,myLen);
            delete[] mString;
        }
        mString = str;
        str += myLen;
        memcpy(str, other, otherLen);
        str[otherLen] = '\0';
        return 0;
    }
    return -1;
}


ssize_t String8::find(const char* other, size_t start) const
{
    size_t len = size();
    if (start >= len) {
        return -1;
    }
    const char* s = mString+start;
    const char* p = strstr(s, other);
    return p ? p-mString : -1;
}

bool String8::removeAll(const char* other) {
    ssize_t index = find(other);
    if (index < 0) return false;

    char* buf = new char[size()];
    if (!buf) return false; // out of memory
    if(mString != NULL){
        memcpy(buf,mString,size());
        delete[] mString ;
    }
    mString  = buf;

    size_t skip = strlen(other);
    size_t len = size();
    size_t tail = index;
    while (size_t(index) < len) {
        ssize_t next = find(other, index + skip);
        if (next < 0) {
            next = len;
        }

        memcpy(buf + tail, buf + index + skip, next - index - skip);
        tail += next - index - skip;
        index = next;
    }
    return true;
}

void String8::toLower()
{
    toLower(0, size());
}

void String8::toLower(size_t start, size_t length)
{
    const size_t len = size();
    if (start >= len) {
        return;
    }
    if (start+length > len) {
        length = len-start;
    }
    char* buf = new char[len];
    if(buf != NULL){
        if(mString != NULL){
            memcpy(buf,mString,len);
            delete[] mString ;
        }
        mString  = buf;
        buf += start;
        while (length > 0) {
            *buf = tolower(*buf);
            buf++;
            length--;
        }
    }
}

void String8::toUpper()
{
    toUpper(0, size());
}

void String8::toUpper(size_t start, size_t length)
{
    const size_t len = size();
    if (start >= len) {
        return;
    }
    if (start+length > len) {
        length = len-start;
    }
    char* buf = new char[len];
    if(buf != NULL){
        if(mString != NULL){
            memcpy(buf,mString,len);
            delete[] mString ;
        }
        mString  = buf;
    }else{
        golden_printfe("no memory \n");
        return ;
    }

    buf += start;
    while (length > 0) {
        *buf = toupper(*buf);
        buf++;
        length--;
    }
}

// ---------------------------------------------------------------------------
// Path functions

void String8::setPathName(const char* name)
{
    setPathName(name, strlen(name));
}

void String8::setPathName(const char* name, size_t len)
{
    char* buf = new char[len];
    if(buf != NULL){
        if(mString != NULL){
            delete[] mString ;
        }
        mString  = buf;
    }else{
        golden_printfe("no memory \n");
        return;
    }

    memcpy(buf, name, len);

    // remove trailing path separator, if present
    if (len > 0 && buf[len-1] == OS_PATH_SEPARATOR)
        len--;
    buf[len] = '\0';
}


String8 String8::getPathLeaf(void) const
{
    const char* cp;
    const char*const buf = mString;

    cp = strrchr(buf, OS_PATH_SEPARATOR);
    if (cp == NULL)
        return String8(*this);
    else
        return String8(cp+1);
}

String8 String8::getPathDir(void) const
{
    const char* cp;
    const char*const str = mString;

    cp = strrchr(str, OS_PATH_SEPARATOR);
    if (cp == NULL)
        return String8("");
    else
        return String8(str, cp - str);
}

String8 String8::walkPath(String8* outRemains) const
{
    const char* cp;
    const char*const str = mString;
    const char* buf = str;

    cp = strchr(buf, OS_PATH_SEPARATOR);
    if (cp == buf) {
        // don't include a leading '/'.
        buf = buf+1;
        cp = strchr(buf, OS_PATH_SEPARATOR);
    }

    if (cp == NULL) {
        String8 res = buf != str ? String8(buf) : *this;
        if (outRemains) *outRemains = String8("");
        return res;
    }

    String8 res(buf, cp-buf);
    if (outRemains) *outRemains = String8(cp+1);
    return res;
}

/*
 * Helper function for finding the start of an extension in a pathname.
 *
 * Returns a pointer inside mString, or NULL if no extension was found.
 */
char* String8::find_extension(void) const
{
    const char* lastSlash;
    const char* lastDot;
    const char* const str = mString;

    // only look at the filename
    lastSlash = strrchr(str, OS_PATH_SEPARATOR);
    if (lastSlash == NULL)
        lastSlash = str;
    else
        lastSlash++;

    // find the last dot
    lastDot = strrchr(lastSlash, '.');
    if (lastDot == NULL)
        return NULL;

    // looks good, ship it
    return const_cast<char*>(lastDot);
}

String8 String8::getPathExtension(void) const
{
    char* ext;

    ext = find_extension();
    if (ext != NULL)
        return String8(ext);
    else
        return String8("");
}

String8 String8::getFullExtension() const {
    const char* lastSlash;
    const char* const str = mString;
    const char* firstDot;

    // only look at the filename
    lastSlash = strrchr(str, OS_PATH_SEPARATOR);
    if (lastSlash == NULL)
        lastSlash = str;
    else
        lastSlash++;

    // find the last dot
    firstDot = strchr(lastSlash, '.');
    if (firstDot == NULL){
        return String8("");
    }else{
        return String8(firstDot+1);
    }
}

String8 String8::getBasePath(void) const
{
    char* ext;
    const char* const str = mString;

    ext = find_extension();
    if (ext == NULL)
        return String8(*this);
    else
        return String8(str, ext - str);
}

String8& String8::appendPath(const char* name)
{
    // TODO: The test below will fail for Win32 paths. Fix later or ignore.
    if (name[0] != OS_PATH_SEPARATOR) {
        if (*name == '\0') {
            // nothing to do
            return *this;
        }

        size_t len = length();
        if (len == 0) {
            // no existing filename, just use the new one
            setPathName(name);
            return *this;
        }

        // make room for oldPath + '/' + newPath
        int newlen = strlen(name);

        char* buf = new char[(len+1+newlen)];
        if(buf != NULL){
            if(mString != NULL){
                memcpy(buf,mString,len);
                delete[] mString;
            }
            mString = buf;
        }else{
            golden_printfe("no memory \n");
            return *(new String8());
        }

        // insert a '/' if needed
        if (buf[len-1] != OS_PATH_SEPARATOR)
            buf[len++] = OS_PATH_SEPARATOR;

        memcpy(buf+len, name, newlen+1);
        len += newlen;

        return *this;
    } else {
        setPathName(name);
        return *this;
    }
}

String8& String8::convertToResPath()
{
#if OS_PATH_SEPARATOR != RES_PATH_SEPARATOR
    size_t len = length();
    if (len > 0) {
        char * buf = lockBuffer(len);
        for (char * end = buf + len; buf < end; ++buf) {
            if (*buf == OS_PATH_SEPARATOR)
                *buf = RES_PATH_SEPARATOR;
        }
        unlockBuffer(len);
    }
#endif
    return *this;
}

String8 String8::getStringValue(char delimite){
    if(mString == NULL){
        return String8(NULL);
    }

    golden_printfi("####%p %s %s\n",mString,mString,__func__);
    const char* p = strchr(mString, delimite);
    if(p != NULL){
        p++;
        while(*p == ' '){
            p++;
        }
        golden_printfi("%p %s %s\n",mString,mString,__func__);
        return String8(p);
    }else{
        return String8(NULL);
    }
}
