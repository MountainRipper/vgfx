#ifndef OPENGLTEXTURE_H
#define OPENGLTEXTURE_H

#include "opengl_headers.h"

namespace digitools::vgfx {

class OpenGlTexture : public IGraphicTexture {
public:
    OpenGlTexture();

    int32_t create_from_file(const eastl::string &file_path) override;

    int32_t create_from_image(ITexture *texture, uint8_t *image, uint32_t size, int32_t width, int32_t height) override;

    int32_t create_from_image_file(ITexture *texture, const char *image_file) override;

    int32_t create_from_compressed_texture(ITexture *texture, uint8_t *image, uint32_t size) override;

    int32_t create_from_compressed_texture_file(ITexture *texture, const char *image_file) override;

    int32_t create_from_platform_hardware_frame(ITexture *texture, uint8_t *image, int32_t width, int32_t height,
                                                HardareFrameType type) override;

    int32_t create_from_external(ITexture *texture, uint64_t texture_id) override;

private:
    int32_t create_texture();
    int32_t release();
private:
    VGFX_GL_CHECK_VARIANT;
    GLuint texture_ = 0;
};

}//namespace digitools::vgfx


#endif // OPENGLTEXTURE_H
