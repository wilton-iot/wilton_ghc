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
 * File:   dyload_ghc_posix.cpp
 * Author: alex
 *
 * Created on March 17, 2018, 4:36 PM
 */

#include "dyload_ghc.hpp"

#include <dlfcn.h>

#include "staticlib/support.hpp"

#include "wilton/support/exception.hpp"

namespace wilton {
namespace ghc {

namespace { // anonymous

std::string dlerr_str() {
    auto res = ::dlerror();
    return nullptr != res ? std::string(res) : "";
}

} // namespace

void* load_library(const std::string& path) {
    auto lib = ::dlopen(path.c_str(), RTLD_LAZY);
    if (nullptr == lib) {
        throw support::exception(TRACEMSG(
                "Error loading shared library on path: [" + path + "]," +
                " error: [" + dlerr_str() + "]"));
    }
    return lib;
}

void* find_symbol(void* lib, const std::string& name) {
    auto sym = ::dlsym(lib, name.c_str());
    if (nullptr == sym) {
        throw support::exception(TRACEMSG(
                "Error loading symbol: [" + name + "], " +
                " error: [" + dlerr_str() + "]"));
    }
    return sym;
}

} // namespace
}
