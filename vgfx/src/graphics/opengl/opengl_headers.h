#ifndef OPENGL_HEADERS_H
#define OPENGL_HEADERS_H

#include "common.h"

extern "C" {

#if defined(VGFX_OS_ANDROID) || defined(VGFX_OS_LINUX) || defined(VGFX_OS_BSD)
#include <glad/egl.h>
#define OPENGL_HAS_EGL 1
#endif

#if defined(VGFX_OS_LINUX) || defined(VGFX_OS_BSD)
#include <glad/glx.h>
#define OPENGL_HAS_GLX 1
#endif

#if defined(VGFX_OS_WINDOWS)
#include <glad/wgl.h>
#define OPENGL_HAS_WGL 1
#endif

//Windows and Linux can also run GLES via glx/egl/angle, use glad/gl.h are also working
#if defined(VGFX_OS_LINUX) || defined(VGFX_OS_BSD) || defined(VGFX_OS_WINDOWS) || defined(VGFX_OS_MACOS)
#include <glad/gl.h>
#define OPENGL_HAS_GLCORE 1
#endif

#if defined(VGFX_OS_ANDROID)
#include <glad/gles2.h>
#define OPENGL_HAS_GLES 1
#endif

}

//iOS use static link
#if TARGET_OS_IPHONE && TARGET_IPHONE_SIMULATOR
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#endif

#define VGFX_GL_CHECK_VARIANT GLenum gl_error = GL_NO_ERROR;
#define VGFX_GL_CHECK_BREAK if(gl_error != GL_NO_ERROR) break;

#define VGFX_GL_CHECK(level, format, ...) \
{\
    gl_error = GL_NO_ERROR;\
    while(GLenum err = glGetError()){\
        MR_LOG_MORE(level,"OpenGL Call Failed:{} {}",err,mr::fmt_format(format,##__VA_ARGS__));\
        gl_error = err;\
    }\
}

#define VGFX_GL_CHECK_TRACE(format, ...) VGFX_GL_CHECK(mr::Logger::kLogLevelTrace,format,##__VA_ARGS__)
#define VGFX_GL_CHECK_DEBUG(format, ...) VGFX_GL_CHECK(mr::Logger::kLogLevelDebug,format,##__VA_ARGS__)
#define VGFX_GL_CHECK_INFO(format, ...)  VGFX_GL_CHECK(mr::Logger::kLogLevelInfo,format,##__VA_ARGS__)
#define VGFX_GL_CHECK_WARN(format, ...)  VGFX_GL_CHECK(mr::Logger::kLogLevelWarn,format,##__VA_ARGS__)
#define VGFX_GL_CHECK_ERROR(format, ...) VGFX_GL_CHECK(mr::Logger::kLogLevelError,format,##__VA_ARGS__)
#define VGFX_GL_CHECK_FATAL(format, ...) VGFX_GL_CHECK(mr::Logger::kLogLevelFatal,format,##__VA_ARGS__)


#define VGFX_GL_CALL_CHECK(level, call, format, ...) \
{\
    gl_error = GL_NO_ERROR;\
    (call);\
    while(GLenum err = glGetError()){\
        MR_LOG_MORE(level,"OpenGL Call Failed:{} {}",err,mr::fmt_format(format,##__VA_ARGS__));\
        gl_error = err;\
    }\
}

#define VGFX_GL_CALL_CHECK_TRACE(call, format, ...) VGFX_GL_CALL_CHECK(mr::Logger::kLogLevelTrace,call,format,##__VA_ARGS__)
#define VGFX_GL_CALL_CHECK_DEBUG(call, format, ...) VGFX_GL_CALL_CHECK(mr::Logger::kLogLevelDebug,call,format,##__VA_ARGS__)
#define VGFX_GL_CALL_CHECK_INFO(call, format, ...)  VGFX_GL_CALL_CHECK(mr::Logger::kLogLevelInfo,call,format,##__VA_ARGS__)
#define VGFX_GL_CALL_CHECK_WARN(call, format, ...)  VGFX_GL_CALL_CHECK(mr::Logger::kLogLevelWarn,call,format,##__VA_ARGS__)
#define VGFX_GL_CALL_CHECK_ERROR(call, format, ...) VGFX_GL_CALL_CHECK(mr::Logger::kLogLevelError,call,format,##__VA_ARGS__)
#define VGFX_GL_CALL_CHECK_FATAL(call, format, ...) VGFX_GL_CALL_CHECK(mr::Logger::kLogLevelFatal,call,format,##__VA_ARGS__)

#define VGFX_GL_CALL_CHECK_BREAK(level, call, format, ...) \
{\
    gl_error = GL_NO_ERROR;\
    (call);\
    while(GLenum err = glGetError()){\
        MR_LOG_MORE(level,"OpenGL Call Failed:{} {}",err,mr::fmt_format(format,##__VA_ARGS__));\
        gl_error = err;\
    }\
    if(gl_error != GL_NO_ERROR)\
        break;\
}
#define VGFX_GL_CALL_CHECK_BREAK_TRACE(call, format, ...) VGFX_GL_CALL_CHECK_BREAK(mr::Logger::kLogLevelTrace,call,format,##__VA_ARGS__)
#define VGFX_GL_CALL_CHECK_BREAK_DEBUG(call, format, ...) VGFX_GL_CALL_CHECK_BREAK(mr::Logger::kLogLevelDebug,call,format,##__VA_ARGS__)
#define VGFX_GL_CALL_CHECK_BREAK_INFO(call, format, ...)  VGFX_GL_CALL_CHECK_BREAK(mr::Logger::kLogLevelInfo,call,format,##__VA_ARGS__)
#define VGFX_GL_CALL_CHECK_BREAK_WARN(call, format, ...)  VGFX_GL_CALL_CHECK_BREAK(mr::Logger::kLogLevelWarn,call,format,##__VA_ARGS__)
#define VGFX_GL_CALL_CHECK_BREAK_ERROR(call, format, ...) VGFX_GL_CALL_CHECK_BREAK(mr::Logger::kLogLevelError,call,format,##__VA_ARGS__)
#define VGFX_GL_CALL_CHECK_BREAK_FATAL(call, format, ...) VGFX_GL_CALL_CHECK_BREAK(mr::Logger::kLogLevelFatal,call,format,##__VA_ARGS__)
#endif // OPENGL_HEADERS_H
