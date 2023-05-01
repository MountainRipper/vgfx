//
// Created by xuwei on 22-11-26.
//

#include "image_loader.h"

enum class ImageFileType : int8_t{
    kImageFileTypeNone = 0,
    kImageFileTypeJPG,
    kImageFileTypePNG,
    kImageFileTypeBMP,
    kImageFileTypeTIFF,
    kImageFileTypeGIF,
    kImageFileTypeTGA,
    kImageFileTypeHDR
};
namespace digitools::vgfx {

//most of them from https://github.com/sindresorhus/file-type/blob/main/core.js, respect
int32_t get_file_type_by_magic(const uint8_t *buf, std::string &type, std::string &mime) {

    if (buf[0] == 0xFF && buf[1] == 0xD8 && buf[2] == 0xFF) {
        type = "jpg";
        mime = "image/jpeg";
        return 0;
    }

    if (buf[0] == 0x89 && buf[1] == 0x50 && buf[2] == 0x4E && buf[3] == 0x47) {
        type = "png";
        mime = "image/png";
        return 0;
    }


    if (buf[0] == 0x42 && buf[1] == 0x4D) {
        type = "bmp";
        mime = "image/bmp";
        return 0;
    }

    if (buf[0] == 0x47 && buf[1] == 0x49 && buf[2] == 0x46) {
        type = "gif";
        mime = "image/gif";
        return 0;
    }

    const uint8_t ktx_magic[] = {0xAB, 0x4B, 0x54, 0x58, 0x20, 0x31, 0x31, 0xBB, 0x0D, 0x0A, 0x1A, 0x0A};
    if(memcmp(buf,ktx_magic,sizeof(ktx_magic))==0){
        type = "ktx";
        mime = "image/ktx";
    }

    //https://github.com/ARM-software/astc-encoder/blob/main/Docs/FileFormat.md
    if (buf[0] == 0x13 && buf[1] == 0xAB && buf[2] == 0xA1 && buf[3] == 0x5C) {
        type = "astc";
        mime = "image/astc";
        return 0;
    }

    //https://learn.microsoft.com/en-us/windows/win32/direct3ddds/dx-graphics-dds-pguide#dds-file-layout
    if (buf[0] == 0x44 && buf[1] == 0x44 && buf[2] == 0x53 && buf[3] == 0x20) {
        type = "dds";
        mime = "image/dds";
        return 0;
    }

    //https://docs.imgtec.com/specifications/pvr-file-format-specification/topics/pvr-header-format.html
    if (buf[0] == 0x50 && buf[1] == 0x56 && buf[2] == 0x52 && buf[3] == 0x03) {
        type = "pvr";
        mime = "image/pvr";
        return 0;
    }

    //stb_image.h
    const char hdr_magic[] = "#?RADIANCE";
    const char hdr_magic_rgb[] = "#?RGBE";
    if(memcmp(buf,hdr_magic,10)==0 || memcmp(buf,hdr_magic_rgb,6)==0){
        type = "hdr";
        mime = "image/hdr";
    }

    //https://github.com/AcademySoftwareFoundation/openexr/wiki/OpenEXR-File-Layout
    if (buf[0] == 0x76 && buf[1] == 0x2f && buf[2] == 0x31 && buf[3] == 0x01) {
        type = "exr";
        mime = "image/exr";
        return 0;
    }

    //stb_image.h
    if (buf[0] == 'P' && (buf[1] == '5' || buf[1] == '6')) {
        type = "pnm";
        mime = "image/pnm";
        return 0;
    }

    if (buf[8] == 0x57 && buf[9] == 0x45 && buf[10] == 0x42 && buf[11] == 0x50) {
        type = "webp";
        mime = "image/webp";
        return 0;
    }

    // needs to be before `tif` check
    if (((buf[0] == 0x49 && buf[1] == 0x49 && buf[2] == 0x2A && buf[3] == 0x0) ||
         (buf[0] == 0x4D && buf[1] == 0x4D && buf[2] == 0x0 && buf[3] == 0x2A)) && buf[8] == 0x43 && buf[9] == 0x52) {
        type = "cr2";
        mime = "image/x-canon-cr2";
        return 0;
    }


    if ((buf[0] == 0x49 && buf[1] == 0x49 && buf[2] == 0x2A && buf[3] == 0x0) ||
        (buf[0] == 0x4D && buf[1] == 0x4D && buf[2] == 0x0 && buf[3] == 0x2A)) {
        type = "tif";
        mime = "image/tiff";
        return 0;
    }

    if (buf[0] == 0x49 && buf[1] == 0x49 && buf[2] == 0xBC) {
        type = "jxr";
        mime = "image/vnd.ms-photo";
        return 0;
    }

    if (buf[0] == 0x38 && buf[1] == 0x42 && buf[2] == 0x50 && buf[3] == 0x53) {
        type = "psd";
        mime = "image/vnd.adobe.photoshop";
        return 0;
    }

    // needs to be before `zip` check
    if (buf[0] == 0x50 && buf[1] == 0x4B && buf[2] == 0x3 && buf[3] == 0x4 && buf[30] == 0x6D && buf[31] == 0x69 &&
        buf[32] == 0x6D && buf[33] == 0x65 && buf[34] == 0x74 && buf[35] == 0x79 && buf[36] == 0x70 &&
        buf[37] == 0x65 && buf[38] == 0x61 && buf[39] == 0x70 && buf[40] == 0x70 && buf[41] == 0x6C &&
        buf[42] == 0x69 && buf[43] == 0x63 && buf[44] == 0x61 && buf[45] == 0x74 && buf[46] == 0x69 &&
        buf[47] == 0x6F && buf[48] == 0x6E && buf[49] == 0x2F && buf[50] == 0x65 && buf[51] == 0x70 &&
        buf[52] == 0x75 && buf[53] == 0x62 && buf[54] == 0x2B && buf[55] == 0x7A && buf[56] == 0x69 &&
        buf[57] == 0x70) {
        type = "epub";
        mime = "application/epub+zip";
        return 0;
    }

    // needs to be before `zip` check
    // assumes signed .xpi from addons.mozilla.org
    if (buf[0] == 0x50 && buf[1] == 0x4B && buf[2] == 0x3 && buf[3] == 0x4 && buf[30] == 0x4D && buf[31] == 0x45 &&
        buf[32] == 0x54 && buf[33] == 0x41 && buf[34] == 0x2D && buf[35] == 0x49 && buf[36] == 0x4E &&
        buf[37] == 0x46 && buf[38] == 0x2F && buf[39] == 0x6D && buf[40] == 0x6F && buf[41] == 0x7A &&
        buf[42] == 0x69 && buf[43] == 0x6C && buf[44] == 0x6C && buf[45] == 0x61 && buf[46] == 0x2E &&
        buf[47] == 0x72 && buf[48] == 0x73 && buf[49] == 0x61) {
        type = "xpi";
        mime = "application/x-xpinstall";
        return 0;
    }

    if (buf[0] == 0x50 && buf[1] == 0x4B && (buf[2] == 0x3 || buf[2] == 0x5 || buf[2] == 0x7) &&
        (buf[3] == 0x4 || buf[3] == 0x6 || buf[3] == 0x8)) {
        type = "zip";
        mime = "application/zip";
        return 0;
    }

    if (buf[257] == 0x75 && buf[258] == 0x73 && buf[259] == 0x74 && buf[260] == 0x61 && buf[261] == 0x72) {
        type = "tar";
        mime = "application/x-tar";
        return 0;
    }

    if (buf[0] == 0x52 && buf[1] == 0x61 && buf[2] == 0x72 && buf[3] == 0x21 && buf[4] == 0x1A && buf[5] == 0x7 &&
        (buf[6] == 0x0 || buf[6] == 0x1)) {
        type = "rar";
        mime = "application/x-rar-compressed";
        return 0;
    }

    if (buf[0] == 0x1F && buf[1] == 0x8B && buf[2] == 0x8) {
        type = "gz";
        mime = "application/gzip";
        return 0;
    }

    if (buf[0] == 0x42 && buf[1] == 0x5A && buf[2] == 0x68) {
        type = "bz2";
        mime = "application/x-bzip2";
        return 0;
    }

    if (buf[0] == 0x37 && buf[1] == 0x7A && buf[2] == 0xBC && buf[3] == 0xAF && buf[4] == 0x27 && buf[5] == 0x1C) {
        type = "7z";
        mime = "application/x-7z-compressed";
        return 0;
    }

    if (buf[0] == 0x78 && buf[1] == 0x01) {
        type = "dmg";
        mime = "application/x-apple-diskimage";
        return 0;
    }

    if (
            (buf[0] == 0x0 && buf[1] == 0x0 && buf[2] == 0x0 && (buf[3] == 0x18 || buf[3] == 0x20) && buf[4] == 0x66 &&
             buf[5] == 0x74 && buf[6] == 0x79 && buf[7] == 0x70) ||
            (buf[0] == 0x33 && buf[1] == 0x67 && buf[2] == 0x70 && buf[3] == 0x35) ||
            (buf[0] == 0x0 && buf[1] == 0x0 && buf[2] == 0x0 && buf[3] == 0x1C && buf[4] == 0x66 && buf[5] == 0x74 &&
             buf[6] == 0x79 && buf[7] == 0x70 && buf[8] == 0x6D && buf[9] == 0x70 && buf[10] == 0x34 &&
             buf[11] == 0x32 && buf[16] == 0x6D && buf[17] == 0x70 && buf[18] == 0x34 && buf[19] == 0x31 &&
             buf[20] == 0x6D && buf[21] == 0x70 && buf[22] == 0x34 && buf[23] == 0x32 && buf[24] == 0x69 &&
             buf[25] == 0x73 && buf[26] == 0x6F && buf[27] == 0x6D) ||
            (buf[0] == 0x0 && buf[1] == 0x0 && buf[2] == 0x0 && buf[3] == 0x1C && buf[4] == 0x66 && buf[5] == 0x74 &&
             buf[6] == 0x79 && buf[7] == 0x70 && buf[8] == 0x69 && buf[9] == 0x73 && buf[10] == 0x6F &&
             buf[11] == 0x6D) ||
            (buf[0] == 0x0 && buf[1] == 0x0 && buf[2] == 0x0 && buf[3] == 0x1c && buf[4] == 0x66 && buf[5] == 0x74 &&
             buf[6] == 0x79 && buf[7] == 0x70 && buf[8] == 0x6D && buf[9] == 0x70 && buf[10] == 0x34 &&
             buf[11] == 0x32 && buf[12] == 0x0 && buf[13] == 0x0 && buf[14] == 0x0 && buf[15] == 0x0)
            ) {
        type = "mp4";
        mime = "video/mp4";
        return 0;
    }

    if ((buf[0] == 0x0 && buf[1] == 0x0 && buf[2] == 0x0 && buf[3] == 0x1C && buf[4] == 0x66 && buf[5] == 0x74 &&
         buf[6] == 0x79 && buf[7] == 0x70 && buf[8] == 0x4D && buf[9] == 0x34 && buf[10] == 0x56)) {
        type = "m4v";
        mime = "video/x-m4v";
        return 0;
    }

    if (buf[0] == 0x4D && buf[1] == 0x54 && buf[2] == 0x68 && buf[3] == 0x64) {
        type = "mid";
        mime = "audio/midi";
        return 0;
    }

    // needs to be before the `webm` check
    if (buf[31] == 0x6D && buf[32] == 0x61 && buf[33] == 0x74 && buf[34] == 0x72 && buf[35] == 0x6f &&
        buf[36] == 0x73 && buf[37] == 0x6B && buf[38] == 0x61) {
        type = "mkv";
        mime = "video/x-matroska";
        return 0;
    }

    if (buf[0] == 0x1A && buf[1] == 0x45 && buf[2] == 0xDF && buf[3] == 0xA3) {
        type = "webm";
        mime = "video/webm";
        return 0;
    }

    if (buf[0] == 0x0 && buf[1] == 0x0 && buf[2] == 0x0 && buf[3] == 0x14 && buf[4] == 0x66 && buf[5] == 0x74 &&
        buf[6] == 0x79 && buf[7] == 0x70) {
        type = "mov";
        mime = "video/quicktime";
        return 0;
    }

    if (buf[0] == 0x52 && buf[1] == 0x49 && buf[2] == 0x46 && buf[3] == 0x46 && buf[8] == 0x41 && buf[9] == 0x56 &&
        buf[10] == 0x49) {
        type = "avi";
        mime = "video/x-msvideo";
        return 0;
    }

    if (buf[0] == 0x30 && buf[1] == 0x26 && buf[2] == 0xB2 && buf[3] == 0x75 && buf[4] == 0x8E && buf[5] == 0x66 &&
        buf[6] == 0xCF && buf[7] == 0x11 && buf[8] == 0xA6 && buf[9] == 0xD9) {
        type = "wmv";
        mime = "video/x-ms-wmv";
        return 0;
    }

    if (buf[0] == 0x0 && buf[1] == 0x0 && buf[2] == 0x1 && (buf[3] & 0xF0) == 0xb0) {
        type = "mpg";
        mime = "video/mpeg";
        return 0;
    }

    if ((buf[0] == 0x49 && buf[1] == 0x44 && buf[2] == 0x33) || (buf[0] == 0xFF && buf[1] == 0xfb)) {
        type = "mp3";
        mime = "audio/mpeg";
        return 0;
    }

    if ((buf[4] == 0x66 && buf[5] == 0x74 && buf[6] == 0x79 && buf[7] == 0x70 && buf[8] == 0x4D && buf[9] == 0x34 &&
         buf[10] == 0x41) || (buf[0] == 0x4D && buf[1] == 0x34 && buf[2] == 0x41 && buf[3] == 0x20)) {
        type = "m4a";
        mime = "audio/m4a";
        return 0;
    }

    // needs to be before `ogg` check
    if (buf[28] == 0x4F && buf[29] == 0x70 && buf[30] == 0x75 && buf[31] == 0x73 && buf[32] == 0x48 &&
        buf[33] == 0x65 && buf[34] == 0x61 && buf[35] == 0x64) {
        type = "opus";
        mime = "audio/opus";
        return 0;
    }

    if (buf[0] == 0x4F && buf[1] == 0x67 && buf[2] == 0x67 && buf[3] == 0x53) {
        type = "ogg";
        mime = "audio/ogg";
        return 0;
    }

    if (buf[0] == 0x66 && buf[1] == 0x4C && buf[2] == 0x61 && buf[3] == 0x43) {
        type = "flac";
        mime = "audio/x-flac";
        return 0;
    }

    if (buf[0] == 0x52 && buf[1] == 0x49 && buf[2] == 0x46 && buf[3] == 0x46 && buf[8] == 0x57 && buf[9] == 0x41 &&
        buf[10] == 0x56 && buf[11] == 0x45) {
        type = "wav";
        mime = "audio/x-wav";
        return 0;
    }

    if (buf[0] == 0x23 && buf[1] == 0x21 && buf[2] == 0x41 && buf[3] == 0x4D && buf[4] == 0x52 && buf[5] == 0x0A) {
        type = "amr";
        mime = "audio/amr";
        return 0;
    }

    if (buf[0] == 0x25 && buf[1] == 0x50 && buf[2] == 0x44 && buf[3] == 0x46) {
        type = "pdf";
        mime = "application/pdf";
        return 0;
    }

    if (buf[0] == 0x4D && buf[1] == 0x5A) {
        type = "exe";
        mime = "application/x-msdownload";
        return 0;
    }

    if ((buf[0] == 0x43 || buf[0] == 0x46) && buf[1] == 0x57 && buf[2] == 0x53) {
        type = "swf";
        mime = "application/x-shockwave-flash";
        return 0;
    }

    if (buf[0] == 0x7B && buf[1] == 0x5C && buf[2] == 0x72 && buf[3] == 0x74 && buf[4] == 0x66) {
        type = "rtf";
        mime = "application/rtf";
        return 0;
    }

    if (
            (buf[0] == 0x77 && buf[1] == 0x4F && buf[2] == 0x46 && buf[3] == 0x46) &&
            (
                    (buf[4] == 0x00 && buf[5] == 0x01 && buf[6] == 0x00 && buf[7] == 0x00) ||
                    (buf[4] == 0x4F && buf[5] == 0x54 && buf[6] == 0x54 && buf[7] == 0x4F)
            )
            ) {
        type = "woff";
        mime = "application/font-woff";
        return 0;
    }

    if (
            (buf[0] == 0x77 && buf[1] == 0x4F && buf[2] == 0x46 && buf[3] == 0x32) &&
            (
                    (buf[4] == 0x00 && buf[5] == 0x01 && buf[6] == 0x00 && buf[7] == 0x00) ||
                    (buf[4] == 0x4F && buf[5] == 0x54 && buf[6] == 0x54 && buf[7] == 0x4F)
            )
            ) {
        type = "woff2";
        mime = "application/font-woff";
        return 0;
    }

    if (
            (buf[34] == 0x4C && buf[35] == 0x50) &&
            (
                    (buf[8] == 0x00 && buf[9] == 0x00 && buf[10] == 0x01) ||
                    (buf[8] == 0x01 && buf[9] == 0x00 && buf[10] == 0x02) ||
                    (buf[8] == 0x02 && buf[9] == 0x00 && buf[10] == 0x02)
            )
            ) {
        type = "eot";
        mime = "application/octet-stream";
        return 0;
    }

    if (buf[0] == 0x00 && buf[1] == 0x01 && buf[2] == 0x00 && buf[3] == 0x00 && buf[4] == 0x00) {
        type = "ttf";
        mime = "application/font-sfnt";
        return 0;
    }

    if (buf[0] == 0x4F && buf[1] == 0x54 && buf[2] == 0x54 && buf[3] == 0x4F && buf[4] == 0x00) {
        type = "otf";
        mime = "application/font-sfnt";
        return 0;
    }

    if (buf[0] == 0x00 && buf[1] == 0x00 && buf[2] == 0x01 && buf[3] == 0x00) {
        type = "ico";
        mime = "image/x-icon";
        return 0;
    }

    if (buf[0] == 0x46 && buf[1] == 0x4C && buf[2] == 0x56 && buf[3] == 0x01) {
        type = "flv";
        mime = "video/x-flv";
        return 0;
    }

    if (buf[0] == 0x25 && buf[1] == 0x21) {
        type = "ps";
        mime = "application/postscript";
        return 0;
    }

    if (buf[0] == 0xFD && buf[1] == 0x37 && buf[2] == 0x7A && buf[3] == 0x58 && buf[4] == 0x5A && buf[5] == 0x00) {
        type = "xz";
        mime = "application/x-xz";
        return 0;
    }

    if (buf[0] == 0x53 && buf[1] == 0x51 && buf[2] == 0x4C && buf[3] == 0x69) {
        type = "sqlite";
        mime = "application/x-sqlite3";
        return 0;
    }

    if (buf[0] == 0x4E && buf[1] == 0x45 && buf[2] == 0x53 && buf[3] == 0x1A) {
        type = "nes";
        mime = "application/x-nintendo-nes-rom";
        return 0;
    }

    if (buf[0] == 0x43 && buf[1] == 0x72 && buf[2] == 0x32 && buf[3] == 0x34) {
        type = "crx";
        mime = "application/x-google-chrome-extension";
        return 0;
    }

    if (
            (buf[0] == 0x4D && buf[1] == 0x53 && buf[2] == 0x43 && buf[3] == 0x46) ||
            (buf[0] == 0x49 && buf[1] == 0x53 && buf[2] == 0x63 && buf[3] == 0x28)
            ) {
        type = "cab";
        mime = "application/vnd.ms-cab-compressed";
        return 0;
    }

    // needs to be before `ar` check
    if (buf[0] == 0x21 && buf[1] == 0x3C && buf[2] == 0x61 && buf[3] == 0x72 && buf[4] == 0x63 && buf[5] == 0x68 &&
        buf[6] == 0x3E && buf[7] == 0x0A && buf[8] == 0x64 && buf[9] == 0x65 && buf[10] == 0x62 && buf[11] == 0x69 &&
        buf[12] == 0x61 && buf[13] == 0x6E && buf[14] == 0x2D && buf[15] == 0x62 && buf[16] == 0x69 &&
        buf[17] == 0x6E && buf[18] == 0x61 && buf[19] == 0x72 && buf[20] == 0x79) {
        type = "deb";
        mime = "application/x-deb";
        return 0;
    }

    if (buf[0] == 0x21 && buf[1] == 0x3C && buf[2] == 0x61 && buf[3] == 0x72 && buf[4] == 0x63 && buf[5] == 0x68 &&
        buf[6] == 0x3E) {
        type = "ar";
        mime = "application/x-unix-archive";
        return 0;
    }

    if (buf[0] == 0xED && buf[1] == 0xAB && buf[2] == 0xEE && buf[3] == 0xDB) {
        type = "rpm";
        mime = "application/x-rpm";
        return 0;
    }

    if (
            (buf[0] == 0x1F && buf[1] == 0xA0) ||
            (buf[0] == 0x1F && buf[1] == 0x9D)
            ) {
        type = "Z";
        mime = "application/x-compress";
        return 0;
    }

    if (buf[0] == 0x4C && buf[1] == 0x5A && buf[2] == 0x49 && buf[3] == 0x50) {
        type = "lz";
        mime = "application/x-lzip";
        return 0;
    }

    if (buf[0] == 0xD0 && buf[1] == 0xCF && buf[2] == 0x11 && buf[3] == 0xE0 && buf[4] == 0xA1 && buf[5] == 0xB1 &&
        buf[6] == 0x1A && buf[7] == 0xE1) {
        type = "msi";
        mime = "application/x-msi";
        return 0;
    }

    return kErrorCodeInvalidResource;
};

const char *ImageLoader::filetype(const uint8_t *image_data) {


    return "";
}

MemoryImage ImageLoader::local_from_file(const eastl::string &file_path) {
    return {};
}
}//namespace digitools::vgfx