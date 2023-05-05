#ifndef PIPELINE_H
#define PIPELINE_H
#include "common.h"
namespace mr {
namespace vgfx {

class Engine;
class Pipeline
{
public:

    enum class Status : int8_t{
        kStatusNone,
        kStatusInitializing,
        kStatusReady,
        kStatusFailed,
        kStatusClosing,
        kStatusClosed
    };
    Pipeline(Engine& engine,bool threading = true);
private:
    int32_t render_thread_proc();
private:
    int32_t initialize();
    int32_t execute();
private:
    Engine& owner_engine_;
    bool threading_ = false;
    Status status_ = Status::kStatusNone;
    std::thread render_thread_;
    TSharedPtr<IGraphicContext> graphic_;

    bool quit_ = false;
};


}//namespace vgfx
}//namespace mr

#endif // PIPELINE_H
