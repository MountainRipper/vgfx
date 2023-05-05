#include "pipeline.h"
#include "engine.h"
#include "display.h"
#include "graphics/opengl/graphic_context_glx.h"

namespace mr {
namespace vgfx {

Pipeline::Pipeline(Engine &engine, bool threading)
    :owner_engine_(engine)
    ,threading_(threading)
{
    status_ = Status::kStatusInitializing;
    if(threading_)
        render_thread_ = std::thread(&Pipeline::render_thread_proc,this);
    else
        initialize();
}

int32_t Pipeline::render_thread_proc()
{
    MR_TRACE("Pipeline enter render thread");
    auto ret = initialize();
    if(ret < 0)
        return ret;

    while (!quit_) {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        execute();
    }

    return 0;
}

int32_t Pipeline::initialize()
{
    int32_t ret = 0;
    if(owner_engine_.displayer().params().graphic_platform == GraphicPlatform::kGraphicPlatformGlx){
        #if defined(VGFX_OS_LINUX) || defined(VGFX_OS_BSD)
            graphic_ = SharedPtr<IGraphicContext>(static_cast<IGraphicContext*>(new GraphicContextGlx()));
            ret = graphic_->initialize(owner_engine_.displayer().params());
        #else
            MR_ERROR("System {} not support graphic platform glx",VGFX_OS_NAME);
        #endif
    }
    if(ret < 0){
        status_ = Status::kStatusFailed;
        return ret;
    }
    status_ = Status::kStatusReady;
    return 0;
}

int32_t Pipeline::execute()
{
    return 0;
}


}//namespace vgfx
}//namespace mr
