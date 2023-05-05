#include "opengl_texture.h"
#include <stb/stb_image.h>
namespace mr::vgfx {

OpenGlTexture::OpenGlTexture() {

}

int32_t OpenGlTexture::create_from_resource(const TString& resource_path) {
    return 0;
}

int32_t OpenGlTexture::create_from_image(ITexture *texture, uint8_t *image, uint32_t size, int32_t width, int32_t height) {
    return 0;
}

int32_t OpenGlTexture::create_from_image_file(ITexture *texture, const char *image_file) {
    return 0;
}


int32_t OpenGlTexture::create_from_external(ITexture *texture, uint64_t texture_id) {
    return IGraphicTexture::create_from_external(texture, texture_id);
}

int32_t OpenGlTexture::create_texture() {
    if(texture_ == 0) {
        VGFX_GL_CALL_CHECK_FATAL(glGenTextures(1, &texture_),"glGenTextures failed");
    }
    return 0;
}

int32_t OpenGlTexture::release() {
    if(texture_ > 0){
        VGFX_GL_CALL_CHECK_ERROR(glDeleteTextures(1,&texture_),"glDeleteTextures failed");
        texture_ = 0;
    }
    return 0;
}

}//namespace mr::vgfx
