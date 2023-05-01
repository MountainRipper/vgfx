//
// Created by xuwei on 22-12-2.
//

#ifndef VGFX_OS_ARCH_H
#define VGFX_OS_ARCH_H

static const char* g_os_name[12]={
        "unknown",
        "android",
        "linux",
        "windows",
        "ios",
        "tvos",
        "macos",
        "freebsd",
        "openbsd",
        "netbsd",
        "unix",
        "posix"
};
static const char* g_os_arch[7]={
        "unknown",
        "x86_64",
        "x86",
        "aarch64",
        "armv7a",
        "mips",
        "mips64"
};
#if __ANDROID__
    #define VGFX_OS_TYPE 1
    #define VGFX_OS_ANDROID 1
#elif defined(__linux__) || defined(__LINUX__)
    #define VGFX_OS_TYPE 2
    #define VGFX_OS_LINUX 1
#elif defined(_WIN64) || defined(_WIN32)
    #define VGFX_OS_TYPE 3
   #define VGFX_OS_WINDOWS 1
#elif __APPLE__
#include "TargetConditionals.h"
    #if TARGET_OS_IPHONE && TARGET_IPHONE_SIMULATOR
        #define VGFX_OS_TYPE 4
        #define VGFX_OS_IOS 1
    #elif TARGET_OS_IPHONE
        #define VGFX_OS_TYPE 4
        #define VGFX_OS_IOS 1
    #elif TARGET_OS_TVOS
        #define VGFX_OS_TYPE 5
        #define VGFX_OS_TVOS 1
    #else
        #define VGFX_OS_TYPE 6
        #define VGFX_OS_MACOS 1
    #endif
#elif defined(__FreeBSD__)
#define VGFX_OS_TYPE 7
    #define VGFX_OS_BSD 1
    #define VGFX_OS_FREEBSD 1
#elif defined(__OpenBSD__)
#define VGFX_OS_TYPE 8
    #define VGFX_OS_BSD 1
    #define VGFX_OS_FREEBSD 1
#elif defined(__NetBSD__)
#define VGFX_OS_TYPE 9
    #define VGFX_OS_BSD 1
    #define VGFX_OS_FREEBSD 1
#elif __unix__
    #define VGFX_OS_TYPE 10
    #define VGFX_OS_UNIX 1
#elif __posix
    #define VGFX_OS_TYPE 11
    #define VGFX_OS_POSIX 1
#else
    #define VGFX_OS_TYPE 0
#endif

//https://sourceforge.net/p/predef/wiki/Architectures/
//https://code.qt.io/cgit/qt/qtbase.git/tree/src/corelib/global/qprocessordetection.h
#if __x86_64__ || __x86_64 || __amd64__  || __amd64 || _M_AMD64 || _M_X64
    #define VGFX_ARCH_TYPE 1
    #define VGFX_ARCH_X86_64 1
#elif (__X86__ || _X86_ || __i386__ || __i386 || _M_IX86)
    #define VGFX_ARCH_TYPE 2
    #define VGFX_ARCH_X86 1
#elif (__aarch64__)
    #define VGFX_ARCH_TYPE 3
    #define VGFX_ARCH_AARCH64 1
#elif  (__arm__ || _M_ARM)
    #define VGFX_ARCH_TYPE 4
    #define VGFX_ARCH_ARM 1
#elif (__MIPS__ || __mips__ || __mips )
    #define VGFX_ARCH_TYPE 5
    #define VGFX_ARCH_MIPS 1
#elif  (_MIPS_ARCH_MIPS64) || __mips64)
    #define VGFX_ARCH_TYPE 6
    #define VGFX_ARCH_MIPS64 1
#endif

#define VGFX_OS_NAME g_os_name[VGFX_OS_TYPE]

#endif //VGFX_OS_ARCH_H
