/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2025 TheLGF (LGF-Studio™)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#pragma once

#include <string>
#include <cstring>
#include <cwchar>
#include <cstdlib>

#ifndef TEXT

#if defined(UNICODE) || defined(_UNICODE)
#define TEXT(x) u8##x

#else
#define TEXT(x) x

#endif
#endif

#ifndef strdup
inline char* strdup_(const char* s)
{
    if (!s)
        return nullptr;
    size_t len = std::strlen(s) + 1;
    char* d = (char*)std::malloc(len);
    if (d)
        std::memcpy(d, s, len);
    return d;
}
#else
#define strdup_ strdup
#endif

#ifndef wcsdup
inline wchar_t* wcsdup_(const wchar_t* s)
{
    if (!s)
        return nullptr;
    size_t len = std::wcslen(s) + 1;
    wchar_t* d = (wchar_t*)std::malloc(len * sizeof(wchar_t));
    if (d)
        std::wmemcpy(d, s, len);
    return d;
}
#else
#define wcsdup_ wcsdup
#endif

typedef char chara;
typedef wchar_t charw;

typedef
#if defined(UNICODE) || defined(_UNICODE)
charw
#else
chara
#endif
tchar;

namespace std
{
    typedef basic_string<tchar, char_traits<tchar>, allocator<tchar>> tstring;
    typedef string stringA;
    typedef wstring stringW;
}

inline charw* UseStrFromA(const chara* orig_a)
{
    if (!orig_a) return nullptr;

    size_t _c = std::mbstowcs(nullptr, orig_a, 0);
    if (_c == (size_t)-1) return nullptr;

    charw* _s = new charw[_c+1];
    if (std::mbstowcs(_s, orig_a, _c+1) == (size_t)-1) {
        delete[] _s;
        return nullptr;
    }
    return _s;
}
inline chara* UseStrFromW(const charw* orig_w)
{
    if (!orig_w) return nullptr;

    size_t _c = std::wcstombs(nullptr, orig_w, 0);
    if (_c == (size_t)-1) return nullptr;

    chara* _s = new chara[_c + 1];
    if (std::wcstombs(_s, orig_w, _c + 1) == (size_t)-1) {
        delete[] _s;
        return nullptr;
    }
    return _s;
}
inline tchar* UseTStr(const chara* orig_a)
{
    return
#if defined(UNICODE) || defined(_UNICODE)
        UseStrFromA(orig_a)
#else
        strdup_(orig_a)
#endif
        ;
}
inline tchar* UseTStr(const charw* orig_w)
{
    return
#if defined(UNICODE) || defined(_UNICODE)
        wcsdup_(orig_w)
#else
        UseStrFromW(orig_w)
#endif
        ;
}
inline chara* UseAStr(const tchar* orig_tchar)
{
    return
#if defined(UNICODE) || defined(_UNICODE)
        UseStrFromW(orig_tchar);
#else
        strdup_(orig_tchar)
#endif
        ;
}
inline charw* UseWStr(const tchar* orig_tchar)
{
    return
#if defined(UNICODE) || defined(_UNICODE)
        wcsdup_(orig_tchar)
#else
        UseStrFromA(orig_tchar);
#endif
    ;
}

#undef strdup_
#undef wcsdup_
