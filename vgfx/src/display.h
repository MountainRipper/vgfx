#ifndef __DISPLAY_H__
#define __DISPLAY_H__


#include "common.h"

namespace digitools {
namespace vgfx {

class Engine;
class Displayer : public IDisplayer
{
public:
    Displayer();
    int32_t initialize(DisplayParameters& parameters);
    IEngine* create_engine(EngineParametres& engine_parameters);
    int32_t swap();
    const DisplayParameters& params();
private:
    int32_t initialize_opengl();
    int32_t initialize_vulkan();
private:
    DisplayParameters display_parameters_;    
    TVector<TSharedPtr<Engine>> engines_;
};

}
}


#endif // __DISPLAY_H__