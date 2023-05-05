#ifndef OPENGLPROGRAM_H
#define OPENGLPROGRAM_H
#include "common.h"
#include "opengl_headers.h"

namespace mr::vgfx {

class OpenGLProgram : public IGraphicProgram
{
public:
    OpenGLProgram();
    virtual int32_t create(const TString& vertex_shader,const TString& fragment_shader);
    virtual int32_t valid();
    virtual int32_t use();
private:
    GLuint create_shader(const char* source,GLuint shader_type);
    void release();
private:
    VGFX_GL_CHECK_VARIANT;

    GLuint program_ = 0;
    bool  valid_ = false;
};

}//namespace mr::vgfx



#endif // OPENGLPROGRAM_H
