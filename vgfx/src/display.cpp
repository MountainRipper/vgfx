#include "display.h"
#include "engine.h"
#include "graphics/opengl/opengl_headers.h"
namespace digitools {
namespace vgfx {

Displayer::Displayer()
{

}

int32_t Displayer::initialize(DisplayParameters &parameters)
{
    display_parameters_ = parameters;
    if(display_parameters_.graphic_platform == GraphicPlatform::kGraphicPlatformEgl ||
       display_parameters_.graphic_platform == GraphicPlatform::kGraphicPlatformGlx ||
       display_parameters_.graphic_platform == GraphicPlatform::kGraphicPlatformWgl){
        initialize_opengl();
    }
    if(display_parameters_.graphic_platform == GraphicPlatform::kGraphicPlatformVulkan){
        initialize_vulkan();
    }
    return 0;
}

IEngine *Displayer::create_engine(EngineParametres &engine_parameters)
{
    TSharedPtr<Engine> engine = TSharedPtr<Engine>(new Engine(*this));
    int32_t ret;
    MR_CHECK_FATAL(ret=engine->init(engine_parameters),"Create Engine Failed:params:{},{}",12,"ABC");
    engines_.push_back(engine);
    return nullptr;
}

int32_t Displayer::swap()
{
    return 0;
}

const DisplayParameters &Displayer::params()
{
    return display_parameters_;
}

int32_t Displayer::initialize_opengl()
{
    auto start_clock = std::chrono::high_resolution_clock::now();
    if(display_parameters_.graphic_platform == GraphicPlatform::kGraphicPlatformGlx){
#if defined(OPENGL_HAS_GLX)
        if(!glXGetCurrentContext){
            MR_CHECK_FATAL_BOOL(gladLoaderLoadGLX((Display*)display_parameters_.display,0),"glad cant't load glx library");
        }
#else
        MR_FATAL("the {} system not support GLX backend",VGFX_OS_NAME);
#endif

    }
    else if(display_parameters_.graphic_platform == GraphicPlatform::kGraphicPlatformEgl){
#if defined(OPENGL_HAS_EGL)
        if(!eglGetCurrentContext)
            MR_CHECK_FATAL_BOOL(gladLoaderLoadEGL(NULL),"glad cant't load egl library");
#else
        MR_FATAL("the {} system not support EGL backend",VGFX_OS_NAME);
#endif
    }
    else if(display_parameters_.graphic_platform == GraphicPlatform::kGraphicPlatformWgl){
        MR_FATAL("Working...TODO");
    }

#if defined(OPENGL_HAS_GLCORE)
    if(!glClearColor)
        MR_CHECK_FATAL_BOOL(gladLoaderLoadGL(),"glad cant't load gl library");
#endif

#if defined(OPENGL_HAS_GLES)
    if(!glClearColor)
        MR_CHECK_FATAL_BOOL(gladLoaderLoadGLES2(),"glad cant't load gles library");
#endif

    auto ms = (std::chrono::high_resolution_clock::now() - start_clock).count() / 1000000.0;
    MR_TRACE("glad load opengl functions use {} MS",ms);
    return 0;
}

int32_t Displayer::initialize_vulkan(){
    return 0;
}


}//namespace vgfx
}//namespace digitools
