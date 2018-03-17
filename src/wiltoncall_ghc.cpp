/* 
 * File:   wiltoncall_ghc.cpp
 * Author: alex
 *
 * Created on March 17, 2018, 11:35 AM
 */

#include <functional>
#include <string>
#include <vector>

#include "staticlib/ranges.hpp"
#include "staticlib/support.hpp"
#include "staticlib/tinydir.hpp"
#include "staticlib/utils.hpp"

#include "wilton/wilton_ghc.h"

#include "wilton/support/buffer.hpp"
#include "wilton/support/misc.hpp"
#include "wilton/support/logging.hpp"
#include "wilton/support/registrar.hpp"

namespace wilton {
namespace ghc {

namespace { // anonymous

std::string default_lib_dir() {
    auto exepath = sl::utils::current_executable_path();
    auto exedir_raw = sl::utils::strip_filename(exepath);
    return sl::tinydir::normalize_path(exedir_raw);
}

std::string platform_libname(const std::string& name) {
#ifdef STATICLIB_WINDOWS
    return name + ".dll";
#elif defined(STATICLIB_MAC)
    return std::string("lib") + name + ".dylib";
#else // !STATICLIB_MAC
    return std::string("lib") + name + ".so";
#endif
}

} // namespace

support::buffer init(sl::io::span<const char> data) {
    // json parse
    auto json = sl::json::load(data);
    auto libname = std::string("wilton_ghcshim");
    auto dir = std::string();
    auto options = std::vector<std::string>();
    for (const sl::json::field& fi : json.as_object()) {
        auto& name = fi.name();
        if ("shimLibName" == name) {
            libname = fi.as_string_nonempty_or_throw(name);
        } else if ("shimLibDirectory" == name) {
            dir = fi.as_string_nonempty_or_throw(name);
        } else if ("initArgs" == name) {
            options = sl::ranges::transform(fi.as_array_or_throw(name), [&name](const sl::json::value& en) {
                return en.as_string_nonempty_or_throw(name);
            }).to_vector();
        } else {
            throw support::exception(TRACEMSG("Unknown data field: [" + name + "]"));
        }
    }
    if (dir.empty()) {
        dir = default_lib_dir();
    }
    // prepare args
    auto path = dir + "/" + platform_libname(libname);
    options.insert(options.begin(), "wilton");
    auto args = sl::ranges::transform(options, [](const std::string& ar) {
        return ar.c_str();
    }).to_vector();
    // call wilton
    char* err = wilton_ghc_init(path.c_str(), static_cast<int>(path.length()),
            static_cast<int>(args.size()), args.data());
    if (nullptr != err) {
        support::throw_wilton_error(err, TRACEMSG(err));
    }
    return support::make_null_buffer();
}

support::buffer shutdown(sl::io::span<const char>) {
    // call wilton
    char* err = wilton_ghc_shutdown();
    if (nullptr != err) {
        support::throw_wilton_error(err, TRACEMSG(err));
    }
    return support::make_null_buffer();
}

support::buffer thread_done(sl::io::span<const char>) {
    // call wilton
    char* err = wilton_ghc_thread_done();
    if (nullptr != err) {
        support::throw_wilton_error(err, TRACEMSG(err));
    }
    return support::make_null_buffer();
}

} // namespace
}

extern "C" char* wilton_module_init() {
    try {
        wilton::support::register_wiltoncall("ghc_init", wilton::ghc::init);
        wilton::support::register_wiltoncall("ghc_shutdown", wilton::ghc::shutdown);
        wilton::support::register_wiltoncall("ghc_thread_done", wilton::ghc::thread_done);
        return nullptr;
    } catch (const std::exception& e) {
        return wilton::support::alloc_copy(TRACEMSG(e.what() + "\nException raised"));
    }
}

