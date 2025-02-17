#ifndef PRIVATE_INTERFACE_H
#define PRIVATE_INTERFACE_H
#include "vgfx_interface.h"
#include "string.h"
#include "common.h"

namespace mr::vgfx {

#define VGFX_IMPLEMENT_OBJECT \
public:                              \
    ResourceType get_type() {return resource_type_;}\
    const char *IObject::get_name() {return name_.c_str();}\
    ResourceStatus IObject::status() return ResourceStatus::kResourceStatusInvalid;} \
protected:                    \
    TString name_;                 \
    ResourceType resource_type_ = ResourceType::kResourceTypeNone;\
    ResourceStatus resource_status_ = ResourceStatus::kResourceStatusInvalid;

static TMap<ValueType,uint8_t> g_data_element_bytes={
        {ValueType::kNumberDataTypeNone,0},
        {ValueType::kNumberDataTypeFloat32,4},
        {ValueType::kNumberDataTypeFloat64,8},
        {ValueType::kNumberDataTypeUint8,1},
        {ValueType::kNumberDataTypeUint16,2},
        {ValueType::kNumberDataTypeUint32,4},
        {ValueType::kNumberDataTypeUint64,8},
        {ValueType::kNumberDataTypeInt8,1},
        {ValueType::kNumberDataTypeInt16,2},
        {ValueType::kNumberDataTypeInt32,4},
        {ValueType::kNumberDataTypeInt64,8},
};
#define VGFX_DATA_TYPE_BYTES(type) ((type>=ValueType::kNumberDataTypeNone && type<=ValueType::kNumberDataTypeInt64)?g_data_element_bytes[type]:0)


template<typename T>
class SharedBuffer{
public:
    static TSharedPtr<T> create_buffer(T* data, size_t count){
        TSharedPtr<T> buffer = TSharedPtr<T>(new T[count],STL::default_delete<T[]>());
        if(data != nullptr)
            memcpy(buffer.get(),data,sizeof(T)*count);
        return buffer;
    }

    SharedBuffer(T* data, size_t count){
        buffer_ = create_buffer(data,count);
        count_ = count;
        type_bytes_ = sizeof(T);
        bytes_ = count * type_bytes_;
    }
    TSharedPtr<T> buffer()     {return buffer_;}
    size_t       bytes()      {return bytes_;}
    size_t       count()      {return count_;}
    size_t       type_bytes() {return type_bytes_;}
private:
    TSharedPtr<T> buffer_;
    size_t bytes_;
    size_t count_;
    size_t type_bytes_;
};

class SharedValueBuffer{
public:
    SharedValueBuffer(uint8_t* data,size_t bytes,ValueType type){
        buffer_     = SharedBuffer<uint8_t>::create_buffer(data, bytes);
        type_       = type;
        bytes_      = bytes;
        type_bytes_ = VGFX_DATA_TYPE_BYTES(type);
        count_      = bytes / type_bytes_;
    }
    SharedValueBuffer(const SharedValueBuffer& data){
        buffer_     = data.buffer_;
        type_       = data.type_;
        bytes_      = data.bytes_;
        type_bytes_ = data.type_bytes_;
        count_      = data.count_;
    }
    uint8_t * buffer(){
        if(!buffer_)
            return nullptr;
        return buffer_.get();
    }

    template<typename T> T* buffer_as(){
        if(buffer_)
            return nullptr;
        return reinterpret_cast<T*>(buffer_.get());
    }

    size_t count() const{
        return  count_;
    }
    template<typename T> size_t count_as(){
        return bytes_ / sizeof(T);
    }

    size_t bytes() const{
        return bytes_;
    }

    ValueType type() const{
        return type_;
    }
private:
    TSharedPtr<uint8_t> buffer_;
    ValueType type_       = ValueType::kNumberDataTypeNone;
    size_t    bytes_      = 0;
    size_t    count_      = 0;
    uint8_t   type_bytes_ = 0;
};


class IGraphicContext : public  IObject{
public:
    virtual int32_t initialize(const DisplayParameters& params) = 0;
};

class IGraphicProgram : public  IObject{
public:
    virtual int32_t create(const TString& vertex_shader,const TString& fragment_shader) = 0;
    virtual int32_t valid() = 0;
    virtual int32_t use() = 0;
    virtual int32_t test() = 0;
};

class IGraphicTexture : public  IObject{
public:
    virtual int32_t create_from_resource(const TString& resource_path) = 0;
    virtual int32_t create_from_image(ITexture* texture,uint8_t* image,uint32_t size,int32_t width,int32_t height) = 0;
    virtual int32_t create_from_image_file(ITexture* texture,const char* image_file) = 0;
    virtual int32_t create_from_external(ITexture* texture,uint64_t texture_id);
};

class IGraphicFrameBuffer : public  IObject{

};
class IGraphicVertexBuffer : public  IObject{

};

class IGraphicRenderer{
public:
    virtual IGraphicProgram* create_program() = 0;
    virtual IGraphicTexture* create_texture() = 0;
    virtual IGraphicFrameBuffer* create_framebuffer() = 0;
    virtual IGraphicVertexBuffer* create_vertexbuffer() = 0;
};

class ICommand{
public:
    virtual ~ICommand()= default;
    virtual int32_t execute() = 0;
};

}//namespace mr::vgfx
#endif // PRIVATE_INTERFACE_H
