#ifndef RESOURCESTORE_H
#define RESOURCESTORE_H
#include "common.h"
#include <filesystem>
namespace digitools::vgfx {

enum class ResourceFileType : int32_t{
    kResourceTypeNone,
    kResourceTypeVerticeShader,
    kResourceTypeFragmentShader,
    kResourceTypeImage,
    kResourceTypeMesh,
};

struct ResourceData{    
    TSharedPtr<uint8_t> data;
    uint32_t size = 0;
};

class IResourceProvider{
public:
    virtual ~IResourceProvider(){}
    virtual int32_t open(const TString &resource_path) = 0;
    virtual int32_t close() = 0;
    virtual int32_t get_data(const TString& resource_path,ResourceData& data) = 0;
    virtual int32_t get_resource_path(const TString& resource_path,TString& full_path) = 0;
};

class ZipArchiveResourceData;
class ZipArchiveResource : public IResourceProvider
                         , public ObjectHiddenData<ZipArchiveResource,ZipArchiveResourceData>{
public:
    ZipArchiveResource();
    // IResourceProvider interface
public:
    virtual int32_t open(const TString &resource_path);
    virtual int32_t close();
    virtual int32_t get_data(const TString &resource_path, ResourceData &data);
    virtual int32_t get_resource_path(const TString &resource_path, TString &full_path);
private:
};

class DirectoryResource : public IResourceProvider{
public:
    // IResourceProvider interface
public:
    virtual int32_t open(const TString &resource_path);
    virtual int32_t close();
    virtual int32_t get_data(const TString &resource_path, ResourceData &data);
    virtual int32_t get_resource_path(const TString &resource_path, TString &full_path);
private:
    std::filesystem::path root_path_;

};

class ResourceStore : public IResourceStore
{
public:
    ResourceStore();

    // IResourceStore interface
public:
    virtual int32_t append_resource_directory(const char *directory_path);
    virtual int32_t append_resource_bunble(const char *bundle_file_path);
    virtual int32_t release_resource(const char *resource_path);
private:
    TMap<TString,TSharedPtr<IResourceProvider>> providers_;
};


}//namespace digitools::vgfx

#endif // RESOURCESTORE_H
