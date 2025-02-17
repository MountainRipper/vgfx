#include <filesystem>
#include <glad/gl.h>
#include <imgui.h>
#include <ttf/IconsFontAwesome6.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include "bgfx/bgfx.h"
#include "bgfx/platform.h"
#include "hello_vgfx.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_sdl2.h>

MR_MR_SDL_RUNNER_SHOWCASE(HelloVGFX)
class CB : public bgfx::CallbackI{



    // CallbackI interface
public:
    virtual void fatal(const char *_filePath, uint16_t _line, bgfx::Fatal::Enum _code, const char *_str) override
    {
    }
    virtual void traceVargs(const char *_filePath, uint16_t _line, const char *_format, va_list _argList) override
    {
    }
    virtual void profilerBegin(const char *_name, uint32_t _abgr, const char *_filePath, uint16_t _line) override
    {
    }
    virtual void profilerBeginLiteral(const char *_name, uint32_t _abgr, const char *_filePath, uint16_t _line) override
    {
    }
    virtual void profilerEnd() override
    {
    }
    virtual uint32_t cacheReadSize(uint64_t _id) override
    {
        return 0;
    }
    virtual bool cacheRead(uint64_t _id, void *_data, uint32_t _size) override
    {
    }
    virtual void cacheWrite(uint64_t _id, const void *_data, uint32_t _size) override
    {
    }
    virtual void screenShot(const char *_filePath, uint32_t _width, uint32_t _height, uint32_t _pitch, const void *_data, uint32_t _size, bool _yflip) override
    {
        fprintf(stderr,"shot to:%s\n",_filePath);
        stbi_write_png(_filePath,_width,_height,4,(uint8_t*)_data+(_width*4*(_height-1)),-_width*4);
    }
    virtual void captureBegin(uint32_t _width, uint32_t _height, uint32_t _pitch, bgfx::TextureFormat::Enum _format, bool _yflip) override
    {
    }
    virtual void captureEnd() override
    {
    }
    virtual void captureFrame(const void *_data, uint32_t _size) override
    {
    }
};

HelloVGFX::HelloVGFX()
{
}


int32_t HelloVGFX::on_set_params(cxxopts::Options &options)
{
    return 0;
}

int32_t HelloVGFX::on_pre_init(cxxopts::ParseResult &options_result, uint32_t &window_flags)
{
    return 0;
}

const bgfx::ViewId kClearView = 0;
bgfx::FrameBufferHandle fb_;
bgfx::TextureHandle tex_;
void *window_ = nullptr;
CB cb;
#define USE_BGFX_HEADLESS
int32_t HelloVGFX::on_init(void *window,int width, int height)
{
    window_ = window;
    glViewport(0,0,width,height);
    // glClearColor(1.0,0.5,0.0,0.0);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    width_ = width;
    height_ = height;

    bgfx::renderFrame();

    bgfx::Init init;
    memset(&init,0,sizeof(init));

    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo((SDL_Window*)window, &wmInfo);
#if defined(__linux__) && !defined(USE_BGFX_HEADLESS)
    init.platformData.ndt = (void*)wmInfo.info.x11.display;
    init.platformData.nwh = (void*)wmInfo.info.x11.window;
#elif BX_PLATFORM_WINDOWS
    init.platformData.nwh = wmInfo.info.win.window;
#endif


    init.type = bgfx::RendererType::Enum::OpenGL;
    init.callback = &cb;
    init.debug = 1;
    init.platformData.context = SDL_GL_GetCurrentContext();
    init.resolution.width = (uint32_t)width;
    init.resolution.height = (uint32_t)height;
    init.resolution.reset = BGFX_RESET_NONE;

    if (!bgfx::init(init))
        return 1;

    bgfx::setDebug(BGFX_DEBUG_TEXT);
    // Set view 0 to the same dimensions as the window and to clear the color buffer.
    bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH, 0xFF3030ff);
    bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);

    bgfx::setViewClear(1, BGFX_CLEAR_COLOR, 0x0000FFFF);
    bgfx::setViewRect(1, 0, 0, 100,100);

    fb_ = bgfx::createFrameBuffer(width_,height_,bgfx::TextureFormat::RGBA8,
                BGFX_SAMPLER_U_CLAMP|BGFX_SAMPLER_V_CLAMP|BGFX_TEXTURE_BLIT_DST);
    tex_ = bgfx::createTexture2D(width_,height_,false,1,bgfx::TextureFormat::RGBA8, BGFX_TEXTURE_BLIT_DST|BGFX_TEXTURE_READ_BACK);
    return 0;
}

int32_t HelloVGFX::on_deinit()
{
    return 0;
}

int32_t HelloVGFX::on_frame()
{
    // glClearColor(1.0,0.5,0.0,0.0);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static uint8_t *pxs = new uint8_t[width_*height_*4];
    static int cap_num = 0;
    static int c = 0;

    bgfx::touch(kClearView);
    bgfx::setViewFrameBuffer(kClearView,fb_);
    // bgfx::setViewFrameBuffer(kClearView,fb_);
    // Use debug font to print information about this example.
    bgfx::dbgTextClear();
    // bgfx::dbgTextImage(bx::max<uint16_t>(uint16_t(width / 2 / 8), 20) - 20, bx::max<uint16_t>(uint16_t(height / 2 / 16), 6) - 6, 40, 12, s_logo, 160);
    bgfx::dbgTextPrintf(0, 0, 0x0f, "Press F1 to toggle stats.");
    bgfx::dbgTextPrintf(0, 1, 0x0f, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");
    bgfx::dbgTextPrintf(80, 1, 0x0f, "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
    bgfx::dbgTextPrintf(80, 2, 0x0f, "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");
    const bgfx::Stats* stats = bgfx::getStats();
    bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters.", stats->width, stats->height, stats->textWidth, stats->textHeight);
    // Enable stats or debug text.
    bgfx::setDebug(0 ? BGFX_DEBUG_STATS : BGFX_DEBUG_TEXT);
    // Advance to next frame. Process submitted rendering primitives.

    bgfx::setViewRect(1, 100*(c%10), 0, 100,100);
    bgfx::touch(1);
    bgfx::setViewFrameBuffer(1,fb_);
    bgfx::dbgTextPrintf(0, 5, 0x0f, "Press F1 to toggle stats.");

    if(c <= 10){
        bgfx::requestScreenShot(BGFX_INVALID_HANDLE,"/home/xuwei/sc.png");
        auto text = bgfx::getTexture(fb_);
        bgfx::blit(1, tex_, 0, 0, text );
        cap_num = bgfx::readTexture(tex_,pxs);
    }

    auto f_num = bgfx::frame();
    // f_num = bgfx::frame();

    // ImGui_ImplOpenGL3_NewFrame();
    // ImGui_ImplSDL2_NewFrame();
    // ImGui::NewFrame();


    ImGui::Begin("Hello VGFX");
    ImGui::Text("frames:%d",c);
    ImGui::Button("frames");
    ImGui::End();

    // ImGui::Render();
    // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());




    if(c <= 10){
        cap_num = 0;
        char sz[32];
        sprintf(sz,"/home/xuwei/fb-%d.png",c);
        stbi_write_png(sz,width_,height_,4,pxs,width_*4);
    }
    // SDL_GL_SwapWindow((SDL_Window*)window_);
    c++;
    return 0;
}

void HelloVGFX::button_callback(int bt, int type, int clicks, double x, double y)
{

}


void HelloVGFX::cursor_callback(double x, double y)
{
}

void HelloVGFX::key_callback(int key, int type, int scancode, int mods)
{

}


void HelloVGFX::error_callback(int err, const char *desc)
{
}

void HelloVGFX::resize_callback(int width, int height)
{
    width_ = width;
    height_ = height;
    resized_ = true;
}

void HelloVGFX::command(std::string command)
{

}


void HelloVGFX::render_ui()
{

}
