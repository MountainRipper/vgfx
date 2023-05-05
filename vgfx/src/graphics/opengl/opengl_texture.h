#ifndef OPENGLTEXTURE_H
#define OPENGLTEXTURE_H

#include "opengl_headers.h"

namespace mr::vgfx {

class OpenGlTexture : public IGraphicTexture {
public:
    OpenGlTexture();

    int32_t create_from_resource(const TString& resource_path) override;

    int32_t create_from_image(ITexture *texture, uint8_t *image, uint32_t size, int32_t width, int32_t height) override;

    int32_t create_from_image_file(ITexture *texture, const char *image_file) override;

    int32_t create_from_external(ITexture *texture, uint64_t texture_id) override;

private:
    int32_t create_texture();
    int32_t release();
private:
    VGFX_GL_CHECK_VARIANT;
    GLuint texture_ = 0;
};

}//namespace mr::vgfx


#endif // OPENGLTEXTURE_H
