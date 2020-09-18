
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
    return (int)index - offset;
}

#define UNKNOWN_UNICODE 0xFFFD
unsigned int utf8_GetOneUnicode(const char* src, size_t srclen, int* increase)
{
    const unsigned char* p = (const unsigned char*)src;
    size_t left = 0;
    size_t save_srclen = srclen;
    int overlong = 0;
    int underflow = 0;
    unsigned int ch = UNKNOWN_UNICODE;

    if (srclen == 0) {
        return UNKNOWN_UNICODE;
    }
    if (p[0] >= 0xFC) {
        if ((p[0] & 0xFE) == 0xFC) {
            if (p[0] == 0xFC && (p[1] & 0xFC) == 0x80) {
                overlong = 1;
            }
            ch = (unsigned int)(p[0] & 0x01);
            left = 5;
        }
    }
    else if (p[0] >= 0xF8) {
        if ((p[0] & 0xFC) == 0xF8) {
            if (p[0] == 0xF8 && (p[1] & 0xF8) == 0x80) {
                overlong = 1;
            }
            ch = (unsigned int)(p[0] & 0x03);
            left = 4;
        }
    }
    else if (p[0] >= 0xF0) {
        if ((p[0] & 0xF8) == 0xF0) {
            if (p[0] == 0xF0 && (p[1] & 0xF0) == 0x80) {
                overlong = 1;
            }
            ch = (unsigned int)(p[0] & 0x07);
            left = 3;
        }
    }
    else if (p[0] >= 0xE0) {
        if ((p[0] & 0xF0) == 0xE0) {
            if (p[0] == 0xE0 && (p[1] & 0xE0) == 0x80) {
                overlong = 1;
            }
            ch = (unsigned int)(p[0] & 0x0F);
            left = 2;
        }
    }
    else if (p[0] >= 0xC0) {
        if ((p[0] & 0xE0) == 0xC0) {
            if ((p[0] & 0xDE) == 0xC0) {
                overlong = 1;
            }
            ch = (unsigned int)(p[0] & 0x1F);
            left = 1;
        }
    }
    else {
        if ((p[0] & 0x80) == 0x00) {
            ch = (unsigned int)p[0];
        }
    }
    --srclen;
    while (left > 0 && srclen > 0) {
        ++p;
        if ((p[0] & 0xC0) != 0x80) {
            ch = UNKNOWN_UNICODE;
            break;
        }
        ch <<= 6;
        ch |= (p[0] & 0x3F);
        --srclen;
        --left;
    }
    if (left > 0) {
        underflow = 1;
    }
    /* Technically overlong sequences are invalid and should not be interpreted.
       However, it doesn't cause a security risk here and I don't see any harm in
       displaying them. The application is responsible for any other side effects
       of allowing overlong sequences (e.g. string compares failing, etc.)
       See bug 1931 for sample input that triggers this.
    */
    /* if (overlong) return UNKNOWN_UNICODE; */

    (void)overlong;

    if (underflow ||
        (ch >= 0xD800 && ch <= 0xDFFF) ||
        (ch == 0xFFFE || ch == 0xFFFF) || ch > 0x10FFFF) {
        ch = UNKNOWN_UNICODE;
    }

	if (increase) *increase = (int)(save_srclen - srclen);

    return ch;
}
