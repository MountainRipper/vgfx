#ifndef VGFX_INTERFACE_H
#define VGFX_INTERFACE_H
#include <cinttypes>

namespace digitools::vgfx {

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

enum class HardareFrameType : int32_t{
    kHardareFrameNone = 0,
    kHardareFrameAndroidHardwareBuffer,
    kHardareFrameAppleCVPixelBuffer,
    kHardareFrameLinuxVASurface,
    kHardareFrameLinuxDrmFrame,
    kHardareFrameDirectXSurface,
};

enum class SoftwarePixelFormat : int32_t{
    kPixelFormatNone = 0,
    //32bpp
    kPixelFormatRGBA,
    kPixelFormatBGRA,
    //24bpp
    kPixelFormatRGB,
    kPixelFormatBGR,
    //8bpp
    kPixelFormatGray,
    //16bpp
    kPixelFormatGrayAlpha,
    //12bpp yuv420P planner i420 yuv
    kPixelFormatI420,
    //12bpp yuv420P planner yv12 yvu
    kPixelFormatYV12,
    //12bpp yuv420 y-planner uv-packeted
    kPixelFormatNV12,
    //12bpp yuv420 y-planner vu-packeted
    kPixelFormatNV21,
    //16bpp yuv 422 packeted yuyv
    kPixelFormatYUYV422,
    //24bpp yuv 444 packeted
    kPixelFormatYUYV444,
};

enum class TexturePixelFormat : int32_t{
    kTexurePixelFormatNone = 0,
    kTexurePixelFormatRGBA,
    kTexurePixelFormatBGRA,
    kTexurePixelFormatRGB,
    kTexurePixelFormatBGR,
    kTexurePixelFormatLuminance,
    kTexurePixelFormatLuminanceAlpha,
};

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

typedef void(*FunctionReleaseBuffer)(uint8_t*,uint32_t);
struct DecryptResult
{
    uint8_t* data = nullptr;
    uint32_t data_size = 0;
    FunctionReleaseBuffer releaser = nullptr;
};
typedef DecryptResult(*FunctionDecrypt)(const char* name,
                                        const char* file_path,
                                        const uint8_t* data,
                                        uint32_t data_size,
                                        ResourceType type);
struct DisplayParameters
{
    DisplayParameters() {

    }

    /*
    WGL:HWND Handle
    GLX:XID Window
    EGL: EGLNativeWindowType
    NSGL:NSWindow Pointer
    EAGL:NULL
    nullptr for headless
    */
    void* window    = nullptr;
    /*
    WGL:
    GLX:_XDisplay
    EGL: EGLDisplay
    NSGL:NSOpenGLContext Pointer
    EAGL:NULL
    */
    void* display   = nullptr;
    /*
    WGL:HWND Handle
    GLX:XID Window
    EGL: EGLContext
    NSGL:NSWindow Pointer
    EAGL:NULL
    */
    void* context   = nullptr;
    /*
    Graphic api use, for read
    example: when running x11-glx, both OpenGL Core and ES profile can use. (runtime can check actually)
    */
    GraphicPlatform graphic_platform = GraphicPlatform::kGraphicPlatformNone;
};

struct EngineParametres{
    //rendering resolution
    uint16_t width  = 0;
    uint16_t height = 0;
    /*
    rendering thread count
    1 for single thread sync rendering
    */
    uint8_t rendering_threads = 1;

    /*
    resource decrypt callback funtion
    */
    FunctionDecrypt resource_decrypter = nullptr;
};

class IObject{
public:
    virtual ~IObject();
    virtual ResourceType get_type() ;
    virtual const char* get_name() ;
    virtual ResourceStatus status() ;
};

class IResourceStore : public IObject{
public:
    virtual int32_t append_resource_directory(const char* directory_path) = 0;
    virtual int32_t append_resource_bunble(const char* bundle_file_path) = 0;
    virtual int32_t release_resource(const char *resource_path) = 0;
};
class IProgram : public IObject{
public:
    virtual ResourceType type() = 0;
};

class ITexture : public IObject{
public:
    virtual int32_t width() = 0;
    virtual int32_t height() = 0;
    virtual int32_t unsue() = 0;
};

class IFrameBuffer : public IObject{
public:
    virtual int32_t attach(ITexture* texture) = 0;
    virtual int32_t create(int32_t width,int32_t height) = 0;
    virtual ITexture* texture() = 0;
    virtual int32_t width() = 0;
    virtual int32_t height() = 0;
    virtual int32_t read(uint8_t* image) = 0;
};

class IVertexBuffer : public IObject{
public:
    virtual ValueType type() = 0;
    virtual int32_t count() = 0;
    virtual int32_t put(void* buffer, int32_t count, ValueType type) = 0;
};

//render operators of pipeline
class ICommander: public IObject{
public:
    virtual int32_t count() = 0;
    virtual int32_t switch_to_view() = 0;
    virtual int32_t render_to_framebuffer(const char* name) = 0;
    virtual int32_t use_program(const char* name) = 0;
    virtual int32_t use_texture(const char* name,int32_t position) = 0;

    //load resource in pipeline, so the engine can do this in multithread
    virtual int32_t load_resource(const char* name,ResourceType type,bool cache_it) = 0;
    virtual int32_t create_empty_resource(const char* name,ResourceType type,bool cache_it) = 0;
    virtual int32_t release_resource(const char* name,ResourceType type,bool clear_from_cache = false) = 0;
};

//render thread
class IDrawPipeline : public IObject{
public:
    virtual int32_t id() = 0;
    virtual ICommander* commander() = 0;
    virtual int32_t inactive() = 0;

    virtual int32_t texture_from_image(ITexture* texture,uint8_t* image,uint32_t size,int32_t width,int32_t height) = 0;
    virtual int32_t texture_from_image_file(ITexture* texture,const char* image_file) = 0;
    virtual int32_t texture_from_compressed_texture(ITexture* texture,uint8_t* image,uint32_t size) = 0;
    virtual int32_t texture_from_compressed_texture_file(ITexture* texture,const char* image_file)    = 0;
    virtual int32_t texture_from_platform_hardware_frame(ITexture* texture,uint8_t* image,int32_t width,int32_t height,HardareFrameType type) = 0;
    virtual int32_t texture_from_external(ITexture* texture,uint64_t texture_id) = 0;


    virtual int32_t program_from_shader(IProgram* program,const char* vertex_shader,const char* fragment_shader);
};

class IEngine : public IObject{
public:
    virtual int32_t use_resource_store(IResourceStore* store);

    virtual IProgram* get_program(const char* name) = 0;
    virtual ITexture* get_texture(const char* name) = 0;
    virtual IFrameBuffer* get_frame_buffer(const char* name) = 0;
    virtual IVertexBuffer* get_vertex_buffer(const char* name) = 0;
    virtual IDrawPipeline* get_pipeline() = 0;

    //excute will ingro all draw call, only use it for resource operator
    virtual int32_t execute() = 0;
    virtual int32_t frame() = 0;
};

class IDisplayer : public IObject{
public:
    virtual IEngine* create_engine(EngineParametres& engine_params) = 0;
    virtual int32_t swap() = 0;
};

class Global{
public:
    static IDisplayer* create_display(DisplayParameters& display_parameters);
    static IResourceStore* create_resource_store();

    static int32_t set_logo_level(LogLevel level);
    static int32_t enable_file_log(const char* path,int32_t max_size,uint8_t max_files);
    static int32_t disable_file_log();
};

}//namespace digitools::vgfx
#endif // VGFX_INTERFACE_H
