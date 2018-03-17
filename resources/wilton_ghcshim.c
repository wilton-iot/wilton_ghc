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
