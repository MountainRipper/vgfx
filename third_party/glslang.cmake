# bgfx.cmake - bgfx building in cmake
# Written in 2017 by Joshua Brookover <joshua.al.brookover@gmail.com>

# To the extent possible under law, the author(s) have dedicated all copyright
# and related and neighboring rights to this software to the public domain
# worldwide. This software is distributed without any warranty.

# You should have received a copy of the CC0 Public Domain Dedication along with
# this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

if( TARGET glslang )
	return()
endif()

file( GLOB GLSLANG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/glslang/glslang/GenericCodeGen/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/glslang/glslang/MachineIndependent/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/glslang/glslang/MachineIndependent/preprocessor/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/glslang/glslang/HLSL/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/glslang/hlsl/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/glslang/SPIRV/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/glslang/OGLCompilersDLL/*.cpp
)

if( WIN32 )
        list( APPEND GLSLANG_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/glslang/glslang/OSDependent/Windows/ossource.cpp )
else()
        list( APPEND GLSLANG_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/glslang/glslang/OSDependent/Unix/ossource.cpp )
endif()

add_library( glslang STATIC EXCLUDE_FROM_ALL ${GLSLANG_SOURCES} )
target_include_directories( glslang PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/spirv-tools/include
        ${CMAKE_CURRENT_SOURCE_DIR}/spirv-tools/source
        ${CMAKE_CURRENT_SOURCE_DIR}/glslang
        ${CMAKE_CURRENT_SOURCE_DIR}/glslang/glslang/Include
        ${CMAKE_CURRENT_SOURCE_DIR}/glslang/glslang/Public
	
	PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties( glslang PROPERTIES FOLDER "bgfx/3rdparty" )

if( MSVC )
	target_compile_options( glslang PRIVATE
		"/wd4005"
		"/wd4065"
		"/wd4100"
		"/wd4127"
		"/wd4189"
		"/wd4244"
		"/wd4310"
		"/wd4389"
		"/wd4456"
		"/wd4457"
		"/wd4458"
		"/wd4702"
		"/wd4715"
		"/wd4838"
	)
else()
	target_compile_options( glslang PRIVATE
		"-Wno-ignored-qualifiers"
		"-Wno-implicit-fallthrough"
		"-Wno-missing-field-initializers"
		"-Wno-reorder"
		"-Wno-return-type"
		"-Wno-shadow"
		"-Wno-sign-compare"
		"-Wno-switch"
		"-Wno-undef"
		"-Wno-unknown-pragmas"
		"-Wno-unused-function"
		"-Wno-unused-parameter"
		"-Wno-unused-variable"
		"-fno-strict-aliasing"
	)
endif()

if( APPLE )
	target_compile_options( glslang PRIVATE
		"-Wno-c++11-extensions"
		"-Wno-unused-const-variable"
		"-Wno-deprecated-register"
	)
endif()

if( UNIX AND NOT APPLE )
	target_compile_options( glslang PRIVATE
		"-Wno-unused-but-set-variable"
	)
endif()

target_compile_definitions( glslang PRIVATE
	ENABLE_OPT=1
	ENABLE_HLSL=1
)
