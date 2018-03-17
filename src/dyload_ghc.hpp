/* 
 * File:   dyload_ghc.hpp
 * Author: alex
 *
 * Created on March 17, 2018, 4:05 PM
 */

#ifndef WILTON_GHC_DYLOAD_GHC_HPP
#define WILTON_GHC_DYLOAD_GHC_HPP

#include <string>

namespace wilton {
namespace ghc {

void* load_library(const std::string& path);

void* find_symbol(void* lib, const std::string& name);

} // namespace
}


#endif /* WILTON_GHC_DYLOAD_GHC_HPP */

