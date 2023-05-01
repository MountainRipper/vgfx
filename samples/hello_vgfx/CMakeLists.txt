
file( GLOB SOURCE_EXAMPLE *.cpp *.h)

add_executable(hello_vgfx ${SOURCE_EXAMPLE})
target_compile_definitions(hello_vgfx PRIVATE CMAKE_FILE_DIR="${CMAKE_CURRENT_SOURCE_DIR}" USE_GLES=0)
target_include_directories(hello_vgfx PRIVATE)


if(NOT DEFINED ${MP_TARGET_OS})
    set(MP_TARGET_OS ${CMAKE_SYSTEM_NAME})
endif()
string(TOLOWER ${MP_TARGET_OS} MP_TARGET_OS)
if(NOT DEFINED  ${MP_TARGET_ARCH})
    set(MP_TARGET_ARCH ${CMAKE_SYSTEM_PROCESSOR})
endif()


if(${MP_TARGET_OS} MATCHES "linux")
    include_directories(/usr/include/drm)
    target_link_libraries(hello_vgfx  glad mr-common SDL2 drm ssl X11)
elseif(${MP_TARGET_OS} MATCHES "windows")
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set(MP_TARGET_OS "mingw")
        target_link_libraries(hello_vgfx glad  mr-common SDL2.dll dwmapi luajit-5.1.dll )
    endif()
elseif(${MP_TARGET_OS} MATCHES "darwin")

elseif(${MP_TARGET_OS} MATCHES "android")

elseif(${MP_TARGET_OS} MATCHES "ios")
endif()
