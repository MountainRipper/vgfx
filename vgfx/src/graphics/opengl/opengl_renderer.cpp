#include "opengl_renderer.h"

namespace digitools {
namespace vgfx {

OpenGlRender::OpenGlRender()
{

}

IGraphicProgram* OpenGlRender::create_program()
{
    return 0;
}

IGraphicTexture* OpenGlRender::create_texture()
{
    return 0;
}

IGraphicFrameBuffer* OpenGlRender::create_framebuffer()
{
    return 0;
}

IGraphicVertexBuffer* OpenGlRender::create_vertexbuffer()
{
    return 0;
}

}//namespace vgfx
}//namespace digitools

