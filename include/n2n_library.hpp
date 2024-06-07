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

 // n2n_library: Header file for C++/CLR Compiler

#ifdef _M_CEE

#pragma once

#include "edge.h"
#include "supernode.h"

#include <string>

using namespace System;
using namespace System::Runtime::CompilerServices;

namespace N2N_DLL {
    namespace CLR_CPP {
        private ref class StringHelper abstract sealed {
        public:

            // Converts System::String^ to ANSI string (LPCSTR)
            static ::std::string GetNativeStringA(System::String^ str);

            // Converts System::String^ to wide string (LPCWSTR)
            static ::std::wstring GetNativeStringW(System::String^ str);

            //
            static ::std::tstring GetNativeString(System::String^ str) {
                return
#if defined(UNICODE) || defined(_UNICODE)
                    GetNativeStringW(str);
#else
                    GetNativeStringA(str);
#endif
                ;
            }

            [Extension]
            static std::vector<::std::tstring> ToNativeVector(array<System::String^>^ managedArray)
            {
                std::vector<::std::tstring> nativeVector;

                if (managedArray == nullptr)
                    return nativeVector;

                for each(System::String ^ managedString in managedArray)
                {
                    if (managedString != nullptr)
                    {
                        ::std::tstring nativeString = StringHelper::GetNativeString(managedString);
                        nativeVector.push_back(nativeString);
                    }
                    else
                        nativeVector.push_back(::std::tstring());
                }

                return nativeVector;
            }

            [Extension]
            static std::vector<::std::tstring> ToNativeVector(array<System::String^>^ managedArray, bool skipNulls)
            {
                std::vector<::std::tstring> nativeVector;

                if (managedArray == nullptr)
                    return nativeVector;

                for each(System::String ^ managedString in managedArray)
                {
                    if (managedString != nullptr)
                    {
                        ::std::tstring nativeString = StringHelper::GetNativeString(managedString);
                        nativeVector.push_back(nativeString);
                    }
                    else if (!skipNulls)
                        nativeVector.push_back(::std::tstring());
                }

                return nativeVector;
            }
        };
    }

    // Test Macro
//#define N2NMODULE_EDGE

#ifdef N2NMODULE_EDGE
    namespace Edge {

        // Wrapper of native Edge class
        public ref class Wrapper sealed {
        private:
            n2n::edge::Edge* _native = new n2n::edge::Edge();

            ~Wrapper() {
                delete _native;
            }
            !Wrapper() {
                this->~Wrapper();
            }

        public:
            property bool IsRunning
            {
                bool get() { return _native->IsRunning(); }
            }

            int LoadOptions(array<System::String^>^ options) { return _native->LoadOptions(CLR_CPP::StringHelper::ToNativeVector(options)); }
            //int LoadOptionsCLI(int argc, tchar* const argv[]) { return _native->LoadOptionsCLI(argc,argv); }
            int LoadOptionsFile(System::String^ path) { return _native->LoadOptionsFile(CLR_CPP::StringHelper::GetNativeString(path)); }

            bool Start() { return _native->Start(); }
            void NotifyStop() { return _native->NotifyStop(); }
            //bool IsRunning() { return _native->IsRunning(); }
        };

        public ref class StaticFunctions {

        public:
            static int NativeInvoke_main(int argc, array<System::String^>^ argv);
        };

    }
#endif

    // Test Macro
    //#define N2NMODULE_SUPERNODE

#ifdef N2NMODULE_SUPERNODE
    namespace Supernode {

        // Wrapper of native Supernode class
        public ref class Wrapper sealed {
        private:
            n2n::sn::Supernode* _native = new n2n::sn::Supernode();

            ~Wrapper() {
                delete _native;
            }
            !Wrapper() {
                this->~Wrapper();
            }

        public:
            property bool IsRunning
            {
                bool get() { return _native->IsRunning(); }
            }

            int LoadOptions(array<System::String^>^ options) { return _native->LoadOptions(CLR_CPP::StringHelper::ToNativeVector(options)); }
            //int LoadOptionsCLI(int argc, tchar* const argv[]) { return _native->LoadOptionsCLI(argc,argv); }
            int LoadOptionsFile(System::String^ path) { return _native->LoadOptionsFile(CLR_CPP::StringHelper::GetNativeString(path)); }

            ::n2n::IDaemon::DaemonStatus ValidateDaemon() { return _native->ValidateDaemon(); }

            /// <summary>
            /// 
            /// </summary>
            /// <returns>true if a new running is started, false if a running is already existing</returns>
            bool Start() { return _native->Start(); }
            void NotifyStop() { return _native->NotifyStop(); }
            //bool IsRunning() { return _native->IsRunning(); }
        };

        public ref class StaticFunctions {

        public:
            static int NativeInvoke_main(int argc, array<System::String^>^ argv);
        };
    }
#endif

}

#endif
