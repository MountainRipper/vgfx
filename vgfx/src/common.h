#ifndef COMMON_HEADERS_H
#define COMMON_HEADERS_H

#include <EASTL/queue.h>
#include <EASTL/vector.h>
#include <EASTL/list.h>
#include <EASTL/set.h>
#include <EASTL/hash_set.h>
#include <EASTL/map.h>
#include <EASTL/hash_map.h>
#include <EASTL/bitset.h>
#include <EASTL/string.h>
#include <EASTL/shared_ptr.h>
#include <EASTL/scoped_ptr.h>
#include <EASTL/unique_ptr.h>
#include <EASTL/algorithm.h>

#include <thread>
#include <chrono>

namespace STL=eastl;

#ifndef Queue
#define TQueue eastl::queue
#endif

#ifndef Vector
#define TVector eastl::vector
#endif
#ifndef List
#define TList eastl::list
#endif

#ifndef Set
#define TSet eastl::set
#endif

#ifndef HashSet
#define THashSet eastl::hash_set
#endif

#ifndef Map
#define TMap eastl::map
#endif

#ifndef HashMap
#define THashMap eastl::hash_map
#endif

#ifndef Bitset
#define TBitset eastl::bitset
#endif

#ifndef String
#define TString eastl::string
#endif

#ifndef SharedPtr
#define TSharedPtr eastl::shared_ptr
#endif

#ifndef ScopedPtr
#define TScopedPtr eastl::scoped_ptr
#endif
#ifndef UniquePtr
#define TUniquePtr eastl::unique_ptr
#endif

#include <rpmalloc.h>
class RpMallocInitializer{
public:
    RpMallocInitializer(){
        rpmalloc_initialize();
    }
    ~RpMallocInitializer(){
        rpmalloc_finalize();
    }
};
class RpMallocThreadInitializer{
public:
    RpMallocThreadInitializer(){
        rpmalloc_initialize();
    }
    ~RpMallocThreadInitializer(){
        rpmalloc_finalize();
    }
};

#include "private_interface.h"
#include "os_arch.h"
#include <mr/logger.h>



template<typename Owner,typename Data>
class ObjectHiddenData{
  public:
    ObjectHiddenData(Owner* owner){
        data_ = TSharedPtr<Data>(new Data(owner));
    }
  protected:
    TSharedPtr<Data> data_;
};

template<typename T>
class SharedBuffer{
  public:
    static TSharedPtr<T> create(T* data,size_t count){
        TSharedPtr<T> buffer = TSharedPtr<T>(new T[count],STL::default_delete<T[]>());
        if(data != nullptr)
            memcpy(buffer.get(),data,sizeof(T)*count);
        return buffer;
    }
};
#endif // COMMON_HEADERS_H
