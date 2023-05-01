#include "vgfx.h"
#include <stdio.h>
#include <iostream>
#include <thread>
#include "display.h"
#include "object_pool.h"
#include "resource_store.h"
#include "vgfx_interface.h"


#define AS_STR(var) #var
#define EASURE_FUNCTION(func) \
    if(!func) fprintf(stderr,"function %s not found\n",AS_STR(func)); else fprintf(stderr,"function %s found:%p\n",AS_STR(func),func);


namespace digitools::vgfx {

IObject::~IObject()= default;

ResourceType IObject::get_type() {
    return ResourceType::kResourceTypeNone;
}

const char *IObject::get_name() {
    return "";
}

ResourceStatus IObject::status() {
    return ResourceStatus::kResourceStatusInvalid;
}

IDisplayer *GlobalImplement::create(DisplayParameters &display_parameters)
{
    ObjectPool<IDisplayer> ds;
    TSharedPtr<Displayer> monitor = TSharedPtr<Displayer>(new Displayer());

    auto result = monitor->initialize(display_parameters);
    if(result < 0){
        return nullptr;
    }
    monitors_.push_back(monitor);

    TVector<uint8_t>   buffer_;
    buffer_.push_back(9);

    return monitor.get();
}


GlobalImplement &GlobalImplement::get(){
    static GlobalImplement instance;
    return instance;
}

IDisplayer* Global::create_display(DisplayParameters &display_parameters){

    ResourceData data;
    ZipArchiveResource zip;
    zip.open("/home/xuwei/Downloads/Piccolo-main.zip");
    TString s;
    zip.get_resource_path("/sub/a/b/c.txt",s);
    zip.get_data("/sub/a/b/c.txt",data);


    DirectoryResource dir;
    dir.open("/home/xuwei/work/test/filament-test");
    dir.get_resource_path("glad/glad.h",s);
    dir.get_data("glad/glad.h",data);

    return GlobalImplement::get().create(display_parameters);
}

int32_t Global::set_logo_level(LogLevel level)
{
    mr::Logger::set_level(static_cast<mr::Logger::LogLevel>(level));
    return 0;
}

int32_t Global::enable_file_log(const char *path, int32_t max_size, uint8_t max_files)
{
    mr::Logger::enable_file_log(path,max_size,max_files);
    return 0;
}

int32_t Global::disable_file_log()
{
    mr::Logger::disable_file_log();
    return 0;
}

IResourceStore *Global::create_resource_store() {
    return static_cast<IResourceStore*>(new ResourceStore()) ;
}

}//namespace digitools::vgfx
