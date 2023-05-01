
if(VGFX_CROSS_SYSROOT)
    # where is the target environment
    SET(CMAKE_FIND_ROOT_PATH  ${VGFX_CROSS_SYSROOT})
    SET(CMAKE_SYSROOT ${VGFX_CROSS_SYSROOT})

    # search for programs in the build host directories
    SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    # for libraries and headers in the target directories
    SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
endif()

if(VGFX_CROSS_COMPILER)
    if(EXISTS ${VGFX_CROSS_COMPILER}/bin/aarch64-linux-gnu-gcc)
        SET(CMAKE_C_COMPILER ${VGFX_CROSS_COMPILER}/bin/aarch64-linux-gnu-gcc)
        SET(CMAKE_CXX_COMPILER ${VGFX_CROSS_COMPILER}/bin/aarch64-linux-gnu-g++)
        SET(VGFX_CROSS_PREFIX aarch64-linux-gnu-)
        SET(CMAKE_SYSTEM_PROCESSOR aarch64)
        SET(CMAKE_SYSTEM_NAME Linux)
    elseif (EXISTS ${VGFX_CROSS_COMPILER}/bin/arm-linux-gnueabihf-gcc)
        SET(CMAKE_C_COMPILER ${VGFX_CROSS_COMPILER}/bin/arm-linux-gnueabihf-gcc)
        SET(CMAKE_CXX_COMPILER ${VGFX_CROSS_COMPILER}/bin/arm-linux-gnueabihf-g++)
        SET(VGFX_CROSS_PREFIX arm-linux-gnueabihf-)
        SET(CMAKE_SYSTEM_PROCESSOR armv7a)
        SET(CMAKE_SYSTEM_NAME Linux)
    elseif (EXISTS ${VGFX_CROSS_COMPILER}/ndk-build)
        SET(ABI_LIST arm64-v8a armeabi-v7a x86_64 x86)
        if(NOT ANDROID_ABI)
            message(FATAL_ERROR "BUILD ANDROID TARGET MUST SPECIFIED ANDROID_ABI=${ABI_LIST}")
        endif()

        LIST(FIND ABI_LIST ${VGFX_ANDROID_ABI} abiFind)
        if(abiFind EQUAL -1)
            message(FATAL_ERROR "BUILD ANDROID TARGET MUST SPECIFIED VGFX_ANDROID_ABI=${ABI_LIST}")
        endif()

        SET(ARCH_LIST aarch64 armv7a x86_64 x86)
        LIST(GET ARCH_LIST ${abiFind} archGet)
        SET(CMAKE_SYSTEM_PROCESSOR ${archGet})

        SET(CMAKE_SYSTEM_NAME Android)
    elseif()
        message(FATAL_ERROR "CROSS COMPILER CAN'T BE IDENTIFY")
    endif()
endif()

message("CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}  CMAKE_SYSTEM_PROCESSOR:${CMAKE_SYSTEM_PROCESSOR}")