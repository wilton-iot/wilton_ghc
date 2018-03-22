/*
 * Copyright 2018, alex at staticlibs.net
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 
 * File:   wilton_ghc.cpp
 * Author: alex
 *
 * Created on March 17, 2018, 11:34 AM
 */

#include "wilton/wilton_ghc.h"

#include "staticlib/support.hpp"
#include "staticlib/tinydir.hpp"
#include "staticlib/utils.hpp"

#include "wilton/support/alloc.hpp"
#include "wilton/support/exception.hpp"

#include "dyload_ghc.hpp"

namespace { // anonymous

typedef void(*wilton_ghcshim_hs_init_with_rtsopts_type)(int *argc, char **argv[]);

typedef void(*wilton_ghcshim_hs_exit_type)();

typedef void(*wilton_ghcshim_hs_thread_done_type)();

// initialized from wilton_ghc_init
void* shimlib(const std::string& path = "") {
    static void* lib = [&path]{
        return wilton::ghc::load_library(path);
    }();
    return lib;
}

} // namespace


char* wilton_ghc_init(const char* shimlib_path, int shimlib_path_len,
        int argc_with_rtsopts, const char** argv_with_rtsopts) /* noexcept */ {
    if (nullptr == shimlib_path) return wilton::support::alloc_copy(TRACEMSG("Null 'shimlib_path' parameter specified"));
    if (!sl::support::is_uint16_positive(shimlib_path_len)) return wilton::support::alloc_copy(TRACEMSG(
            "Invalid 'shimlib_path_len' parameter specified: [" + sl::support::to_string(shimlib_path_len) + "]"));
    if (!sl::support::is_uint16_positive(argc_with_rtsopts)) return wilton::support::alloc_copy(TRACEMSG(
            "Invalid 'argc_with_rtsopts' parameter specified: [" + sl::support::to_string(argc_with_rtsopts) + "]"));
    if (nullptr == argv_with_rtsopts) return wilton::support::alloc_copy(TRACEMSG("Null 'argv_with_rtsopts' parameter specified"));
    try {
        // check file
        auto path_str = std::string(shimlib_path, static_cast<size_t>(shimlib_path_len));
        auto path = sl::tinydir::path(path_str);
        if (!(path.exists())) {
            throw wilton::support::exception(TRACEMSG("HSrts shared library not found, path: [" + path_str + "]"));
        }
        // load dylib
        auto lib = shimlib(path_str);
        auto fun_ptr = wilton::ghc::find_symbol(lib, "wilton_ghcshim_hs_init_with_rtsopts");
        auto fun = reinterpret_cast<wilton_ghcshim_hs_init_with_rtsopts_type>(fun_ptr);
        auto argv_with_rtsopts_noconst = const_cast<char**>(argv_with_rtsopts);
        // call init
        fun(std::addressof(argc_with_rtsopts), std::addressof(argv_with_rtsopts_noconst));
        return nullptr;
    } catch (const std::exception& e) {
        return wilton::support::alloc_copy(TRACEMSG(e.what() + "\nException raised"));
    }
}

char* wilton_ghc_shutdown() {
    auto fun_ptr = wilton::ghc::find_symbol(shimlib(), "wilton_ghcshim_hs_exit");
    auto fun = reinterpret_cast<wilton_ghcshim_hs_exit_type>(fun_ptr);
    fun();
    return nullptr;
}

char* wilton_ghc_thread_done() {
    auto fun_ptr = wilton::ghc::find_symbol(shimlib(), "wilton_ghcshim_hs_thread_done");
    auto fun = reinterpret_cast<wilton_ghcshim_hs_thread_done_type>(fun_ptr);
    fun();
    return nullptr;
}
