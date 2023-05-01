#ifndef COMMANDQUEUE_H
#define COMMANDQUEUE_H
#include "common.h"
#include "object_pool.h"
namespace digitools::vgfx {

enum class CommandType : int32_t{

};

//texture commands
class CommandCreateTexture : public ICommand{

};
class CommandUpdateTexture : public ICommand{

};
class CommandReadTexture : public ICommand{

};
class CommandResizeTexture : public ICommand{

};
class CommandDestroyTexture : public ICommand{

};

//shader & program & uniform commands
//JUST USE PROGRAM?
//class CommandCreateShader : public ICommand{

//};
//class CommandDestroyShader : public ICommand{

//};
class CommandCreateProgram : public ICommand{

};
class CommandDestroyProgram : public ICommand{

};
class CommandCreateUniform : public ICommand{

};
class CommandDestroyUniform : public ICommand{

};

//vertex array commands
class CommandCreateVertexArray : public ICommand{

};
class CommandDestroyVertexArray : public ICommand{

};
class CommandCreateDynamicVertexArray : public ICommand{

};
class CommandUpdateDynamicVertexArray : public ICommand{

};
class CommandDestroyDynamicVertexArray : public ICommand{

};

//vertex layout commands
class CommandCreateVertexLayout : public ICommand{

};
class CommandDestroyVertexLayout : public ICommand{

};

//index buffer commands
class CommandCreateIndexBuffer : public ICommand{

};
class CommandDestroyIndexBuffer : public ICommand{

};
class CommandCreateDynamicIndexBuffer : public ICommand{

};
class CommandUpdateDynamicIndexBuffer : public ICommand{

};
class CommandDestroyDynamicIndexBuffer : public ICommand{

};

//frame buffer commands
class CommandCreateFrameBuffer : public ICommand{

};
class CommandDestroyFrameBuffer : public ICommand{

};


class CommandQueue
{
public:
    CommandQueue();
    ITexture* create_texture();
private:
    ObjectPool<CommandCreateTexture> create_texture_command_pool_;
};


}//namespace digitools::vgfx

#endif // COMMANDQUEUE_H
