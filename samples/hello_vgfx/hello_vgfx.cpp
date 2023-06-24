#include <filesystem>
#include <glad/gl.h>
#include <imgui.h>
#include <mrcommon/imgui_mr.h>
#include <ttf/IconsFontAwesome6.h>


#include "hello_vgfx.h"

MR_MR_SDL_RUNNER_SHOWCASE(HelloVGFX)

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
int32_t HelloVGFX::on_init(void *window,int width, int height)
{
    width_ = width;
    height_ = height;


    return 0;
}

int32_t HelloVGFX::on_deinit()
{
    return 0;
}

int32_t HelloVGFX::on_frame()
{
    glClearColor(1.0,0.5,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static int c = 0;
    ImGui::Begin("Hello VGFX");
    ImGui::Text("frames:%d",c++);
    ImGui::End();
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
