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

