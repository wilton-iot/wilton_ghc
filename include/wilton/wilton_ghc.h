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
 * File:   wilton_ghc.h
 * Author: alex
 *
 * Created on March 17, 2018, 11:33 AM
 */

#ifndef WILTON_GHC_H
#define WILTON_GHC_H

#include "wilton/wilton.h"

#ifdef __cplusplus
extern "C" {
#endif

char* wilton_ghc_init(
        const char* shimlib_path,
        int shimlib_path_len,
        int argc_with_rtsopts,
        const char** argv_with_rtsopts);

char* wilton_ghc_shutdown();

char* wilton_ghc_thread_done();

#ifdef __cplusplus
}
#endif

#endif /* WILTON_GHC_H */

