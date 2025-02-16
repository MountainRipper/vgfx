
file( GLOB SOURCE_EXAMPLE *.cpp *.h)

add_executable(hello_vgfx ${SOURCE_EXAMPLE})
target_compile_definitions(hello_vgfx PRIVATE CMAKE_FILE_DIR="${CMAKE_CURRENT_SOURCE_DIR}" USE_GLES=0)
target_include_directories(hello_vgfx PRIVATE)


if(NOT DEFINED ${MR_TARGET_OS})
    set(MR_TARGET_OS ${CMAKE_SYSTEM_NAME})
endif()
string(TOLOWER ${MR_TARGET_OS} MR_TARGET_OS)
if(NOT DEFINED  ${MR_TARGET_ARCH})
    set(MR_TARGET_ARCH ${CMAKE_SYSTEM_PROCESSOR})
endif()


if(${MR_TARGET_OS} MATCHES "linux")
    # include_directories(/usr/include/drm)
    target_link_libraries(hello_vgfx  glad mrcommon imgui_stb spdlog SDL2 drm ssl X11)
elseif(${MR_TARGET_OS} MATCHES "windows")
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        target_link_libraries(hello_vgfx glad  mrcommon imgui_stb spdlog SDL2.dll dwmapi luajit-5.1.dll )
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
            target_link_libraries(hello_vgfx glad  mrcommon imgui_stb spdlog SDL2 dwmapi lua51 )
    endif()
elseif(${MR_TARGET_OS} MATCHES "darwin")

elseif(${MR_TARGET_OS} MATCHES "android")

elseif(${MR_TARGET_OS} MATCHES "ios")
endif()
