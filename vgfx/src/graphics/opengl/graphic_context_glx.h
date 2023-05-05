#ifndef GRAPHICCONTEXT_H
#define GRAPHICCONTEXT_H

#include <common.h>

#if defined(VGFX_OS_LINUX) || defined(VGFX_OS_BSD)
namespace mr {
namespace vgfx {

class GraphicContextGlxData;
class GraphicContextGlx : public IGraphicContext
        , public ObjectHiddenData<GraphicContextGlx,GraphicContextGlxData>
{
public:
    GraphicContextGlx();
    int32_t initialize(const DisplayParameters& params) override;
private:
};

}//namespace vgfx
}//namespace mr

#endif // defined(VGFX_OS_LINUX) || defined(VGFX_OS_BSD)
#endif // GRAPHICCONTEXT_H
