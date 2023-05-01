#include "engine.h"
#include "pipeline.h"

namespace digitools {
namespace vgfx {

Engine::Engine(Displayer &displayer)
    :owner_display_(displayer)
{

}

int32_t Engine::init(const EngineParametres &params)
{
    master_pipeline_ = TSharedPtr<Pipeline>(new Pipeline(*this,false));
    for(int index = 0; index < params.rendering_threads;index++){
        auto pipeline = TSharedPtr<Pipeline>(new Pipeline(*this));
        pipelines_.push_back(pipeline);
    }    
    return 0;
}

Displayer &Engine::displayer()
{
    return owner_display_;
}

}//namespace vgfx
}//namespace digitools
