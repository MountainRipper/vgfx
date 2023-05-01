#ifndef RENDEROPENGL_H
#define RENDEROPENGL_H

#include "common.h"

namespace digitools
{
namespace vgfx
{

class OpenGlRender : public IGraphicRenderer
{
public:
    OpenGlRender();

        virtual IGraphicProgram* create_program();
        virtual IGraphicTexture* create_texture();
        virtual IGraphicFrameBuffer* create_framebuffer();
        virtual IGraphicVertexBuffer* create_vertexbuffer();
};      


}//namespace vgfx
}//namespace digitools



#endif // RENDEROPENGL_H
