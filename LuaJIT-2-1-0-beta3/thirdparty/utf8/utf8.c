/**
*  $Id: md5lib.c,v 1.10 2008/05/12 20:51:27 carregal Exp $
*  Cryptographic and Hash functions for Lua
*  @author  Roberto Ierusalimschy
*/


#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lua.h"
#include "lauxlib.h"

#include "utf8.h"

#ifdef _WIN32
#include <Windows.h>
#endif

int utf8_GetByteCountOfOneWord(unsigned char first_char)
{
    unsigned char temp = 0x80;
    int num = 0;

    unsigned char char_value = first_char;

    if (char_value < 0x80) // ascii code.(0-127)
        return 1;
    while (temp & char_value)
    {
        ++num;
        temp = temp >> 1;
    }

    return num;
}

const char* utf8_UTF82ANSI(const char* content)
{
#ifdef _WIN32
    // 先将UTF-8转换为Unicode
    size_t len = MultiByteToWideChar(CP_UTF8, 0, content, -1, NULL, 0);
    WCHAR* wsz = (WCHAR*)malloc(sizeof(WCHAR) * (len + 1));
    memset(wsz, 0, sizeof(WCHAR) * (len + 1));
    MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)content, -1, wsz, (int)(len));
    // 再将Unicode转换成ANSI
    len = WideCharToMultiByte(CP_ACP, 0, wsz, -1, NULL, 0, NULL, NULL);
    char* sz = (char*)malloc(sizeof(char) * (len + 1));
    memset(sz, 0, sizeof(char) * (len + 1));
    WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wsz, -1, sz, (int)(len), NULL, NULL);
    free(wsz);
    return sz;
#else
    return 0;
#endif
}

const char* utf8_ANSI2UTF8(const char* content)
{
#ifdef _WIN32
    // 先将ANSI转换为Unciode
    int len = MultiByteToWideChar(CP_ACP, 0, content, -1, NULL, 0);
    WCHAR* wsz = (WCHAR*)malloc(sizeof(WCHAR) * (len + 1));
    memset(wsz, 0, sizeof(WCHAR) * (len + 1));
    MultiByteToWideChar(CP_ACP, 0, content, -1, wsz, len);
    // 再将Unicode转换成ANSI
    len = WideCharToMultiByte(CP_UTF8, 0, wsz, -1, NULL, 0, NULL, NULL);
    char* sz = (char*)malloc(sizeof(char) * (len + 1));
    memset(sz, 0, sizeof(char) * (len + 1));
    WideCharToMultiByte(CP_UTF8, 0, wsz, -1, sz, len, NULL, NULL);
    free(wsz);
    return sz;
#else
    return 0;
#endif
}

int utf8_CalcWordCount(const char* str)
{
    int count = 0;
    size_t index = 0;
    while (str[index] != 0)
    {
        index += utf8_GetByteCountOfOneWord(str[index]);
        ++count;
    }
    return count;
}

int utf8_CalcByteCountByWordCount(const char* str, int offset, int word_count)
{
    int count = 0;
    size_t index = offset;
    while (str[index] != 0)
    {
        index += utf8_GetByteCountOfOneWord(str[index]);
        ++count;
        if (count >= word_count) break;
    }
    return (int)index;
}
