# bgfx.cmake - bgfx building in cmake
# Written in 2017 by Joshua Brookover <joshua.al.brookover@gmail.com>

# To the extent possible under law, the author(s) have dedicated all copyright
# and related and neighboring rights to this software to the public domain
# worldwide. This software is distributed without any warranty.

# You should have received a copy of the CC0 Public Domain Dedication along with
# this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

if( TARGET spirv-tools )
	return()
endif()

file(
	GLOB
	SPIRV_TOOLS_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/spirv-tools/source/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/spirv-tools/source/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/spirv-tools/source/opt/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/spirv-tools/source/opt/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/spirv-tools/source/reduce/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/spirv-tools/source/reduce/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/spirv-tools/source/util/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/spirv-tools/source/util/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/spirv-tools/source/val/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/spirv-tools/source/val/*.h
)

add_library( spirv-tools STATIC ${SPIRV_TOOLS_SOURCES} )
target_include_directories( spirv-tools PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/spirv-headers/include
        ${CMAKE_CURRENT_SOURCE_DIR}/spirv-tools
        ${CMAKE_CURRENT_SOURCE_DIR}/spirv-tools/include
        ${CMAKE_CURRENT_SOURCE_DIR}/spirv-tools/include/generated
        ${CMAKE_CURRENT_SOURCE_DIR}/spirv-tools/source
)

if( MSVC )
	target_compile_options( spirv-tools PRIVATE
		"/wd4127"
		"/wd4389"
		"/wd4702"
		"/wd4706"
	)
else()
	target_compile_options( spirv-tools PRIVATE
		"-Wno-switch"
	)

	if(MINGW OR ${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
		target_compile_options( spirv-tools PRIVATE
			"-Wno-misleading-indentation"
		)
	endif()
endif()

set_target_properties( spirv-tools PROPERTIES FOLDER "bgfx/3rdparty" )
