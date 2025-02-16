
SET(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR})
########################### EASTL
# aux_source_directory(${THIRD_PARTY_DIR}/eastl/source EASTL_SOURCE)
# add_library( eastl STATIC ${EASTL_SOURCE} )
# target_include_directories(eastl PUBLIC ${THIRD_PARTY_DIR}/eastl/include)

########################### rpmalloc
# file( GLOB RPMALLOC_SOURCE ${THIRD_PARTY_DIR}/rpmalloc/*.h ${THIRD_PARTY_DIR}/rpmalloc/*.c)
# add_library( rpmalloc STATIC ${RPMALLOC_SOURCE} )
# target_include_directories(rpmalloc PUBLIC ${THIRD_PARTY_DIR}/rpmalloc)

###########################
# add_subdirectory(ozz-animation)

###########################
# file( GLOB TINYEXR_SOURCE ${THIRD_PARTY_DIR}/tinyexr/*.h ${THIRD_PARTY_DIR}/tinyexr/*.cc)
# add_library( tinyexr STATIC ${TINYEXR_SOURCE} )
# target_include_directories(tinyexr PUBLIC ${THIRD_PARTY_DIR}/tinyexr)

#include(glslang.cmake)
#include(spirv-tools.cmake)
#include(spirv-cross.cmake)
