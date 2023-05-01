//
// Created by xuwei on 22-11-26.
//

#ifndef VGFX_IMAGE_LOADER_H
#define VGFX_IMAGE_LOADER_H
#include "../common.h"

namespace digitools::vgfx{

class MemoryImage{
public:
    MemoryImage()=default;
private:
    TSharedPtr<uint8_t> buffer_;
    uint32_t  width_ = 0;
    uint32_t  height_ = 0;
    uint32_t  linesize[4];
    uint32_t  plane[4];
    uint8_t bpp_ = 0;
    uint8_t channels_ = 0;
    SoftwarePixelFormat format_ = SoftwarePixelFormat::kPixelFormatNone;
};


class ImageLoader {
    static const char * filetype(const uint8_t* image_data);
    static MemoryImage local_from_file(const TString& file_path);
};

}//namespace digitools::vgfx


#endif //VGFX_IMAGE_LOADER_H
