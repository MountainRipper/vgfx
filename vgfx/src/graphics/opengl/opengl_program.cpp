
#include "opengl_program.h"

namespace digitools {
namespace vgfx {

OpenGLProgram::OpenGLProgram() {

}

int32_t OpenGLProgram::create(const TString &vertex_shader, const TString &fragment_shader) {
    valid_ = false;
    GLuint gl_vertex_shader = create_shader(vertex_shader.c_str(), GL_VERTEX_SHADER);
    GLuint gl_fragment_shader = create_shader(fragment_shader.c_str(), GL_VERTEX_SHADER);

    if (gl_vertex_shader > 0 && gl_fragment_shader > 0) {
        do {
            VGFX_GL_CALL_CHECK_BREAK_ERROR(program_ = glCreateProgram(), "glCreateProgram")

            VGFX_GL_CALL_CHECK_BREAK_ERROR(glAttachShader(program_, gl_vertex_shader), "glAttachShader vertex shader")
            VGFX_GL_CALL_CHECK_BREAK_ERROR(glAttachShader(program_, gl_fragment_shader),"glAttachShader fragment shader")
            VGFX_GL_CALL_CHECK_BREAK_ERROR(glLinkProgram(program_), "glLinkProgram")

            GLint status = 0;
            VGFX_GL_CALL_CHECK_BREAK_ERROR(glGetProgramiv(program_, GL_LINK_STATUS, &status), "glGetUniformLocation");

            if (status != GL_TRUE) {

                GLchar message[1024];
                GLsizei length = 0;
                VGFX_GL_CALL_CHECK_ERROR(glGetProgramInfoLog(program_, 1024, &length, message), "glGetProgramInfoLog")
                MR_ERROR("OpenGL program create failed:\n{}\nvertex shader:\n{}\nfragment shader:\n{}\n", message,vertex_shader.c_str(), fragment_shader.c_str());
            } else
                valid_ = true;
        } while (false);

        if (!valid_)
            release();
    }

    if (gl_vertex_shader > 0) {
        if (valid_){
            VGFX_GL_CALL_CHECK_ERROR(glDetachShader(program_, gl_vertex_shader), "glDetachShader");
        }
        VGFX_GL_CALL_CHECK_ERROR(glDeleteShader(gl_vertex_shader), "glDeleteShader");
    }

    if (gl_fragment_shader > 0) {
        if (valid_){
            VGFX_GL_CALL_CHECK_ERROR(glDetachShader(program_, gl_fragment_shader), "glDetachShader");
        }
        VGFX_GL_CALL_CHECK_ERROR(glDeleteShader(gl_fragment_shader), "glDeleteShader");
    }

    return valid_ ? 0 : kErrorCodeInvalidResource;
}


int32_t OpenGLProgram::valid() {
    return valid_;
}

int32_t OpenGLProgram::use() {
    if(!valid_)
        return kErrorCodeInvalidArgument;
    glUseProgram(program_);
    return 0;
}

GLuint OpenGLProgram::create_shader(const char *source, GLuint shader_type) {
    GLuint shader = glCreateShader(GL_VERTEX_SHADER);
    VGFX_GL_CHECK_FATAL("glCreateShader")
    if (shader == 0) {
        return 0;
    }

    VGFX_GL_CALL_CHECK_FATAL(glShaderSource(shader, 1, (const GLchar **) &source, nullptr), "glShaderSource shader:{}",source)
    VGFX_GL_CALL_CHECK_FATAL(glCompileShader(shader), "glCompileShader shader")
    return shader;
}

void OpenGLProgram::release() {
    if (program_ > 0)
        glDeleteProgram(program_);
    program_ = 0;
    valid_ = false;
}

}//namespace vgfx
}//namespace digitools
