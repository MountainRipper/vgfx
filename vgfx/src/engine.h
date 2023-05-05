#ifndef ENGINE_H
#define ENGINE_H

#include "common.h"

namespace mr {
namespace vgfx {

class Displayer;
class Pipeline;
class Engine
{
public:
    Engine(Displayer& display);
    int32_t init(const EngineParametres& params);
    Displayer& displayer();
private:
    Displayer& owner_display_;
    TSharedPtr<Pipeline> master_pipeline_;
    TVector<TSharedPtr<Pipeline>> pipelines_;
};

}//namespace vgfx
}//namespace mr

#endif // ENGINE_H
