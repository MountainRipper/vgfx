#include "graphic_context_glx.h"
#include "opengl_headers.h"
#if defined(VGFX_OS_LINUX) || defined(VGFX_OS_BSD)

namespace mr {
namespace vgfx {

class GraphicContextGlxData{
public:
    GraphicContextGlxData(GraphicContextGlx* owner)
        :owner_(owner){

    }
    GraphicContextGlx* owner_;
};

GraphicContextGlx::GraphicContextGlx()
    :ObjectHiddenData(this)
{

}

int32_t GraphicContextGlx::initialize(const DisplayParameters &params)
{
    auto glx_display = (Display*)params.display;
    auto shared_context = (GLXContext)(params.context);
    int usedFbId = -1;
    int r = glXQueryContext(glx_display, shared_context, GLX_FBCONFIG_ID, &usedFbId);
    if (r != 0) {
        MR_FATAL("Failed to get GLX_FBCONFIG_ID from shared GL context. glXQueryContext return:{}",r);
        return -1;
    }
    MR_TRACE("GraphicContextGlx initialize glXQueryContext return:{} get fbid:{}",r,usedFbId);

    int numConfigs = 0;
    GLXFBConfig* fbConfigs = glXGetFBConfigs(glx_display, 0, &numConfigs);

    if (fbConfigs == nullptr) {
        MR_FATAL("Failed to get the available GLXFBConfigs.");
        return -2;
    }

    int fbId = 0;
    int fbIndex = -1;

    for (int i = 0; i < numConfigs; ++i) {
        r = glXGetFBConfigAttrib(glx_display, fbConfigs[i], GLX_FBCONFIG_ID, &fbId);
        if (r != 0) {
            MR_INFO("Failed to get GLX_FBCONFIG_ID for entry {}.", i );
            continue;
        }

        if (fbId == usedFbId) {
            fbIndex = i;
            break;
        }
    }

    if (fbIndex < 0) {
        MR_FATAL("Failed to find an `GLXFBConfig` with the requested ID.");
        return -3;
    }

    auto mGLXConfig = fbConfigs + fbIndex;

    int contextAttribs[] = {
            GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
            GLX_CONTEXT_MINOR_VERSION_ARB, 1,
            GL_NONE
    };

    auto mGLXContext = glXCreateContextAttribsARB(glx_display, mGLXConfig[0],shared_context, True, contextAttribs);
    MR_INFO("GraphicContextGlx initialize glXCreateContextAttribsARB return:{} ",(void*)mGLXContext);
    return 0;
}


}//namespace vgfx
}//namespace mr

#endif // defined(VGFX_OS_LINUX) || defined(VGFX_OS_BSD)
