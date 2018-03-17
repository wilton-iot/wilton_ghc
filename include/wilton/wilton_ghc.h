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

