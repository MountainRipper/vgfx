cmake_minimum_required(VERSION 3.14)

project(vgfx)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # using Clang
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # using GCC
  set(CMAKE_CXX_FLAGS "-fPIC" )
  set(CMAKE_C_FLAGS "-fPIC" )
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  # using Intel C++
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # using Visual Studio C++
  set(CMAKE_CXX_FLAGS "/FS /EHsc" )
  set(CMAKE_C_FLAGS "/FS /EHsc" )
endif()


SET(VGFX_DIR ${CMAKE_CURRENT_SOURCE_DIR})
SET(TARGET_ARCH  ${CMAKE_SYSTEM_PROCESSOR})
SET(SEARCH_LIB_PATHS "")
SET(SEARCHED_LIBS "")
SET(EXTERNAL_SOURCE "")

macro(search_library libName macroDefine debugSuffix)
    SET(libVar ${macroDefine}_LIB)
    SET(libNames "")
    LIST(APPEND libNames ${libName})

    if(${CMAKE_BUILD_TYPE} MATCHES "Debug" AND NOT "${debugSuffix}" STREQUAL "")
        LIST(PREPEND libNames ${libName}${debugSuffix})
    endif()

    find_library(${libVar} NAMES ${libNames} HINTS ${SEARCH_LIB_PATHS})
    if(${libVar} STREQUAL "${libVar}-NOTFOUND")
        message(STATUS "INFO: SEARCH_LIBRARY NOT Fount ${libNames}")
    else()
        message(STATUS "INFO: SEARCH_LIBRARY Fount ${libNames} : ${${libVar}}")
        add_definitions(-D ${macroDefine}=1)
        LIST(APPEND SEARCHED_LIBS ${${libVar}})
    endif()
endmacro(search_library)

link_directories(${SEARCH_LIB_PATHS})

file( GLOB VGFX_SOURCE ${VGFX_DIR}/include/*.h ${VGFX_DIR}/src/*.h ${VGFX_DIR}/src/*.cpp)
file( GLOB COMMON_SOURCE ${VGFX_DIR}/src/common/*.h ${VGFX_DIR}/src/common/*.cpp)
file( GLOB OPENGL_SOURCE ${VGFX_DIR}/src/graphics/opengl/*.h ${VGFX_DIR}/src/graphics/opengl/*.cpp)
add_library(vgfx STATIC
    ${VGFX_SOURCE}
    ${COMMON_SOURCE}
    ${OPENGL_SOURCE}
)

target_include_directories(vgfx PRIVATE ${VGFX_DIR}/src ${VGFX_DIR}/third_party/include)
target_include_directories(vgfx PUBLIC ${VGFX_DIR}/include)
target_link_libraries(vgfx eastl glad spdlog rpmalloc minizip miniz stb yuv X11)
target_compile_definitions(vgfx PRIVATE VIDEOGFX_LIBRARY)

