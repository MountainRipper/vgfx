
#ifndef VGFX_DATA_TYPES_H
#define VGFX_DATA_TYPES_H
#include <cinttypes>
#include <any>
namespace mr::vgfx {

const int32_t kSuccessed                    = 0;
const int32_t kErrorCodeInvalidArgument     = -1;
const int32_t kErrorCodeInvalidStatus       = -2;
const int32_t kErrorCodeInvalidResource     = -3;
const int32_t kErrorCodeInternalError       = -4;
const int32_t kErrorCodeAccessDenied        = -5;
const int32_t kErrorCodeNotExists           = -6;
const int32_t kErrorInvalidProgram          = -7;

const int32_t kSuccessedAlreadyExists        = 1;
//const int32_t kErrorCodeInvalidArgument     = -1;

//same as spdlog::level::level_enum
enum class LogLevel : int32_t{
    kLogLevelTrace = 0,
    kLogLevelDebug,
    kLogLevelInfo,
    kLogLevelWarn,
    kLogLevelError,
    kLogLevelFatal,
    kLogLevelOff
};

enum class SystemType : int32_t{
    kSystemNone = 0,
    kSystemLinux,
    kSystemOSX,
    kSystemWindows,
    kSystemBSD,
    kSystemAndroid,
    kSystemIOS,
};

enum class ArchType : int32_t{
    kArchNone = 0,
    kArchX86_64,
    kArchX86,
    kArchAarch64,
    kArchArm,
    kArchMips,
    kArchLoongArch,
};

enum class GraphicPlatform : int32_t{
    kGraphicPlatformNone = 0,
    /*
    [OpenGL Core/ES]
    Linux/BSD: X11/KMS-DRM/Wayland, both OpenGL Core/ES support
    Android  : only OpenGL ES profile
    Windows  : with ANGLE library,only OpenGL ES profile
    */
    kGraphicPlatformEgl,
    /*
    [OpenGL Core/ES]
    Linux/BSD: running on X11, both OpenGL Core/ES support
    */
    kGraphicPlatformGlx,
    //[OpenGL Core]for Windows WGL
    kGraphicPlatformWgl,
    //[OpenGL Core]for Apple macOS NSGL
    kGraphicPlatformNsgl,
    //[OpenGL ES  ]for Apple iOS EAGL
    kGraphicPlatformEagl,
    //[Vaukan     ]for Vulkan (Linux,Windows,Android)
    kGraphicPlatformVulkan,
    //[OpenGL Core]for Apple Metal (macOS,iOS,tvOS)
    kGraphicPlatformMetal,
};

enum class GraphicApi : int32_t{
    kGraphicApiNone = 0,
    //Windows,Linux,OSX,BSD
    kGraphicApiOpenGL,
    //Windows,Linux,Android,iOS
    kGraphicApiOpenGLES,
    //Windows,Linux,Android
    kGraphicApiVulkan,
    //macOS,iOS,tvOS
    kGraphicApiMetal,
    //windows desktop/uwp, xbox
    kGraphicApiDirect3D12,
    kGraphicApiDirect3D11,
    kGraphicApiDirect3D9
};

//enum class HardareFrameType : int32_t{
//    kHardareFrameNone = 0,
//    kHardareFrameAndroidHardwareBuffer,
//    kHardareFrameAppleCVPixelBuffer,
//    kHardareFrameLinuxVASurface,
//    kHardareFrameLinuxDrmFrame,
//    kHardareFrameDirectXSurface,
//};

//enum class SoftwarePixelFormat : int32_t{
//    kPixelFormatNone = 0,
//    //32bpp
//    kPixelFormatRGBA,
//    kPixelFormatBGRA,
//    //24bpp
//    kPixelFormatRGB,
//    kPixelFormatBGR,
//    //8bpp
//    kPixelFormatGray,
//    //16bpp
//    kPixelFormatGrayAlpha,
//    //12bpp yuv420P planner i420 yuv
//    kPixelFormatI420,
//    //12bpp yuv420P planner yv12 yvu
//    kPixelFormatYV12,
//    //12bpp yuv420 y-planner uv-packeted
//    kPixelFormatNV12,
//    //12bpp yuv420 y-planner vu-packeted
//    kPixelFormatNV21,
//    //16bpp yuv 422 packeted yuyv
//    kPixelFormatYUYV422,
//    //24bpp yuv 444 packeted
//    kPixelFormatYUYV444,
//};

//enum class TexturePixelFormat : int32_t{
//    kTexurePixelFormatNone = 0,
//    kTexurePixelFormatRGBA,
//    kTexurePixelFormatBGRA,
//    kTexurePixelFormatRGB,
//    kTexurePixelFormatBGR,
//    kTexurePixelFormatLuminance,
//    kTexurePixelFormatLuminanceAlpha,
//};

enum class ShaderType : int32_t{
    kShaderNone,
    //OpenGL Core shader
    kShaderGLSL = 1,
    //OpenGL ES shader
    kShaderESSL = 2,
    //microsoft Direct3D shader
    kShaderHLSL = 4,
    //apple Metal shader
    kShaderMSL  = 8,
    //vgfx private binary bundle, put multiple shader format in it
    kShaderMixedBin = 256
};

enum class ValueType : int32_t{
    kNumberDataTypeNone = 0,
    kNumberDataTypeFloat32,
    kNumberDataTypeFloat64,
    kNumberDataTypeUint8,
    kNumberDataTypeUint16,
    kNumberDataTypeUint32,
    kNumberDataTypeUint64,
    kNumberDataTypeInt8,
    kNumberDataTypeInt16,
    kNumberDataTypeInt32,
    kNumberDataTypeInt64,
};

enum class ResourceType : int32_t{
    kResourceTypeNone,
    kResourceTypeProgram,
    kResourceTypeTexture,
    kResourceTypeVertexBuffer,
    kResourceTypeFrameBuffer,
};

enum class ResourceStatus : int32_t{
    kResourceStatusNone = 0,
    kResourceStatusLoading,
    kResourceStatusValid,
    kResourceStatusInvalid,
    kResourceStatusCached
};



}
#endif // VGFX_DATA_TYPES_H
