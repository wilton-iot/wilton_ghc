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
 * File:   dyload_ghc_windows.cpp
 * Author: alex
 *
 * Created on March 17, 2018, 4:36 PM
 */

#include "dyload_ghc.hpp"

#ifndef UNICODE
#define UNICODE
#endif // UNICODE
#ifndef _UNICODE
#define _UNICODE
#endif // _UNICODE
#ifndef NOMINMAX
#define NOMINMAX
#endif NOMINMAX
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "staticlib/support.hpp"
#include "staticlib/utils.hpp"

#include "wilton/support/exception.hpp"

namespace wilton {
namespace ghc {

void* load_library(const std::string& path) {
    auto wpath = sl::utils::widen(path);
    auto lib = ::LoadLibraryW(wpath.c_str());
    if (nullptr == lib) {
        throw support::exception(TRACEMSG(
                "Error loading shared library on path: [" + path + "],"
                " error: [" + sl::utils::errcode_to_string(::GetLastError()) + "]"));
    }
    return lib;
}

void* find_symbol(void* lib, const std::string& name) {
    auto sym = ::GetProcAddress(handle, name.c_str());
    if (nullptr == sym) {
        throw support::exception(TRACEMSG(
                "Error loading symbol: [" + name + "], " +
                " error: [" + sl::utils::errcode_to_string(::GetLastError()) + "]"));
    }
    return sym;
}

} // namespace
}
