//
// Created by xuwei on 22-11-26.
//

#ifndef VGFX_IMAGE_LOADER_H
#define VGFX_IMAGE_LOADER_H
#include "../common.h"

namespace mr::vgfx{


class ImageLoader {
    static const char * filetype(const uint8_t* image_data);
    //static MemoryImage local_from_file(const TString& file_path);
};

}//namespace mr::vgfx


#endif //VGFX_IMAGE_LOADER_H
