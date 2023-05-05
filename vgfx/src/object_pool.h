#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

#include "common.h"

namespace mr {
namespace vgfx {

template<typename T>
class ObjectPool{

    TUniquePtr<T> get(){
        if(objects_.emptr()){
            return new T();
        }
    }
    void recycle(TUniquePtr<T> object){
        objects_.push_back(object);
    }
private:
    TVector<TUniquePtr<T>> objects_;
};

}//namespace vgfx
}//namespace mr


#endif // OBJECT_POOL_H
