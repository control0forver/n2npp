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

#ifdef _M_CEE

#include "n2n_library.hpp"

#include <string>

#include <msclr/marshal.h>

std::string N2N_DLL::CLR_CPP::StringHelper::GetNativeStringA(System::String^ _s)
{
    msclr::interop::marshal_context _mc{};
    return _mc.marshal_as<const char*>(_s);
}

std::wstring N2N_DLL::CLR_CPP::StringHelper::GetNativeStringW(System::String^ _s)
{
    msclr::interop::marshal_context _mc{};
    return _mc.marshal_as<const wchar_t*>(_s);
}

#endif
