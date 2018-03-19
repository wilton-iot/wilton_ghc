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
 * File:   wilton_ghcshim.c
 * Author: alex
 *
 * Created on March 17, 2018, 8:39 PM
 */

// Shim library used to init platform GHC from wilton with "ghc_init" wiltoncall.
//
// Build it with platform GHC:
//
// stack ghc -- --make -dynamic -shared -fPIC -threaded -lHSrts_thr-ghc8.2.2 wilton_ghcshim.c -o libwilton_ghcshim.so

extern void hs_init_with_rtsopts(int *argc, char **argv[]);
extern void wilton_ghcshim_hs_init_with_rtsopts(int *argc, char **argv[]) {
    hs_init_with_rtsopts(argc, argv);
}

extern void hs_exit();
extern void wilton_ghcshim_hs_exit() {
    hs_exit();
}

extern void hs_thread_done();
extern void wilton_ghcshim_hs_thread_done() {
    hs_thread_done();
}
