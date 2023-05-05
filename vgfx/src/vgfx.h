#ifndef VIDEOGFX_H
#define VIDEOGFX_H
#include "common.h"

namespace mr {
namespace vgfx {

class Displayer;

class GlobalImplement{
public:
    static GlobalImplement& get();
    IDisplayer *create(DisplayParameters &environment);
private:
    TVector<TSharedPtr<Displayer>> monitors_;
};


}
}

#endif // VIDEOGFX_H
