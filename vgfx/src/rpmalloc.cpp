//
// Created by xuwei on 22-12-3.
//
#include "common.h"
#include <rpnew.h>
RpMallocInitializer malloc_initializer;

//this is the allocter what eastl need
void* operator new[](size_t size, const char* pName, int flags, unsigned     debugFlags, const char* file, int line)
{
    return rpmalloc(size);
}
void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
    return rpaligned_alloc(alignment,size);
}

void operator delete[](void* ptr, const std::nothrow_t&) EA_THROW_SPEC_DELETE_NONE()
{
    if(ptr)
        rpfree(ptr);
}
#if !defined(WIN32) && !defined(WIN64) && !defined(_MSC_VER)
void operator delete[](void* ptr) EA_THROW_SPEC_DELETE_NONE()
{
    if(ptr)
        rpfree(ptr);
}
//this is the allocter rewrite c++
void* operator new(std::size_t sz)
{
    return rpmalloc(sz);
}
void operator delete(void* ptr) noexcept
{
    if(ptr)
        rpfree(ptr);
}
#endif
