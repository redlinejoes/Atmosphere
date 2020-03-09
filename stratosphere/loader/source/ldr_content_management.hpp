/*
 * Copyright (c) 2018-2020 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include <stratosphere.hpp>

namespace ams::ldr {

    /* Utility reference to make code mounting automatic. */
    class ScopedCodeMount {
        NON_COPYABLE(ScopedCodeMount);
        NON_MOVEABLE(ScopedCodeMount);
        private:
            std::scoped_lock<os::Mutex> lk;
            cfg::OverrideStatus override_status;
            Result result;
            bool has_status;
            bool mounted_ams;
            bool mounted_code;
        public:
            ScopedCodeMount(const ncm::ProgramLocation &loc);
            ScopedCodeMount(const ncm::ProgramLocation &loc, const cfg::OverrideStatus &override_status);
            ~ScopedCodeMount();

            Result GetResult() const {
                return this->result;
            }

            const cfg::OverrideStatus &GetOverrideStatus() const {
                AMS_ABORT_UNLESS(this->has_status);
                return this->override_status;
            }
        private:
            Result Initialize(const ncm::ProgramLocation &loc);
            void EnsureOverrideStatus(const ncm::ProgramLocation &loc);
    };

    constexpr inline const char * const AtmosphereCodeMountName = "ams-code";
    constexpr inline const char * const CodeMountName           = "code";

    #define ENCODE_ATMOSPHERE_CODE_PATH(relative) "ams-code:" relative
    #define ENCODE_CODE_PATH(relative) "ams:" relative

    /* Redirection API. */
    Result ResolveContentPath(char *out_path, const ncm::ProgramLocation &loc);
    Result RedirectContentPath(const char *path, const ncm::ProgramLocation &loc);
    Result RedirectHtmlDocumentPathForHbl(const ncm::ProgramLocation &loc);

}
