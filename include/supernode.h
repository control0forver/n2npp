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

#include <future>

#include "n2n.h"
#include "IOptions.h"
#include "IDaemon.h"

namespace n2n::sn
{
    class Supernode : public IOptions, public IDaemon
    {
        nullable<std::future<int>> _current; // null
        std::atomic<bool> _keep_running;

    public:
        n2n_sn Data {};

    public:
        NATIVELIBRARY_API ~Supernode();

        NATIVELIBRARY_API Supernode();

    protected:
        void OnOptionsLoaded() override;

    public:
        NATIVELIBRARY_API int LoadOptions(const std::vector<std::tstring>& options) override;
        NATIVELIBRARY_API int LoadOptionsCLI(int argc, tchar* const argv[]) override;
        NATIVELIBRARY_API int LoadOptionsFile(const std::tstring& path = "supernode.conf") override;

        NATIVELIBRARY_API ::n2n::IDaemon::DaemonStatus ValidateDaemon() override;

        /// @return true if a new running is started, false if a running is already existing
        NATIVELIBRARY_API bool Start();
        NATIVELIBRARY_API void NotifyStop();
        NATIVELIBRARY_API bool IsRunning() const
        {
            return _current.has_value() && 
                _current.value().wait_for(std::chrono::seconds(0)) != std::future_status::ready;
        }

    private:
        int Run();

    protected:
        // Setup main socket (UDP)
        NATIVELIBRARY_API static int OpenMainSocket(n2n_sn* conf);

        // Setup management socket (UDP)
        NATIVELIBRARY_API static int OpenManagementSocket(n2n_sn* conf);

        // Start auxiliary socket (TCP)
        NATIVELIBRARY_API static int StartAuxiliarySocket(n2n_sn* conf);

        // Assign main UDP socket to all peer_info nodes in the federation
        NATIVELIBRARY_API static int AssignMainSocket(n2n_sn* conf);
        
    public:
        /// @brief This is for internal test purposes only.
        /// @param argc 
        /// @param argv 
        /// @return 
        NATIVELIBRARY_API static int main(int argc, char* const argv[]);
    };

}
