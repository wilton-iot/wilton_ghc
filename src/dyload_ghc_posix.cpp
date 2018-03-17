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
