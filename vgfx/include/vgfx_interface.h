#ifndef VGFX_INTERFACE_H
#define VGFX_INTERFACE_H
#include <functional>
#include "vgfx_data_types.h"
namespace mr::vgfx {


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
//class ICommander: public IObject{
//public:
//    virtual int32_t count() = 0;
//    virtual int32_t switch_to_view() = 0;
//    virtual int32_t render_to_framebuffer(const char* name) = 0;
//    virtual int32_t use_program(const char* name) = 0;
//    virtual int32_t use_texture(const char* name,int32_t position) = 0;

//    //load resource in pipeline, so the engine can do this in multithread
//    virtual int32_t load_resource(const char* name,ResourceType type,bool cache_it) = 0;
//    virtual int32_t create_empty_resource(const char* name,ResourceType type,bool cache_it) = 0;
//    virtual int32_t release_resource(const char* name,ResourceType type,bool clear_from_cache = false) = 0;
//};

//render thread
typedef std::function<int32_t(std::any& resource,ITexture* texture)> TextureLoader;
class IDrawPipeline : public IObject{
public:
    virtual int32_t id() = 0;
    //virtual ICommander* commander() = 0;
    virtual int32_t inactive() = 0;

    virtual int32_t texture_from_resource(ITexture* texture,const char* resource_path);
    virtual int32_t texture_from_image(ITexture* texture,uint8_t* image,uint32_t size,int32_t width,int32_t height) = 0;
    virtual int32_t texture_from_image_file(ITexture* texture,const char* image_file) = 0;
    virtual int32_t texture_from_external(ITexture* texture,uint64_t texture_id) = 0;
    virtual int32_t texture_from_customer_loader(ITexture* texture,std::any resource,TextureLoader loader);

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

}//namespace mr::vgfx
#endif // VGFX_INTERFACE_H
