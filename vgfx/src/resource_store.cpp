#include <miniz.h>
#include <filesystem>
#include "resource_store.h"
namespace mr {
namespace vgfx {


class ZipArchiveResourceData{
public:
    ZipArchiveResourceData(ZipArchiveResource* owner):
    owner_(owner){
        memset(&zip_archive_,0,sizeof(zip_archive_));
    }

    ZipArchiveResource* owner_;
    TString zip_file_path_;
    mz_zip_archive zip_archive_;
    bool opened_ = false;
};

ZipArchiveResource::ZipArchiveResource()
    :ObjectHiddenData(this)
{

}

int32_t ZipArchiveResource::open(const TString &resource_path)
{
    MR_TIMER_NEW(zip_timer);

    data_->zip_file_path_ = resource_path;
    mz_bool ret = mz_zip_reader_init_file(&data_->zip_archive_,resource_path.c_str(),0);
    if(!ret){
        MR_ERROR("open resource zip {} archive faild:{} (bool)",resource_path.c_str(),ret);
        return kErrorCodeInvalidArgument;
    }

    auto files_count = mz_zip_reader_get_num_files(&data_->zip_archive_);

    MR_TRACE("opened resource archive {}, files count:{} use {} MS",resource_path.c_str(),files_count,MR_TIMER_MS(zip_timer));
    data_->opened_ = true;
    return 0;
}

int32_t ZipArchiveResource::close()
{
    if(data_->opened_ == true)
        mz_zip_reader_end(&data_->zip_archive_);
    data_->opened_ = false;
    return 0;
}

int32_t ZipArchiveResource::get_data(const TString &resource_path, ResourceData &data)
{
    if(data_->opened_ == false){
        MR_ERROR_MORE("resource zip archive not opened");
        return kErrorCodeInvalidStatus;
    }

    auto index = mz_zip_reader_locate_file(&data_->zip_archive_,resource_path.c_str(),nullptr,0);
    if(index < 0){
        MR_ERROR_MORE("locate resource  {} in {} failed",resource_path.c_str(),data_->zip_file_path_.c_str());
        return kErrorCodeInvalidResource;
    }
    if(index>=0){
        size_t size = 0;
        auto unzip_data = mz_zip_reader_extract_to_heap(&data_->zip_archive_,index,&size,0);

        if(!unzip_data){
            MR_ERROR_MORE("unzip resource {} in {} failed",resource_path.c_str(),data_->zip_file_path_.c_str());
            return kErrorCodeInvalidArgument;
        }
        data.data = SharedBuffer<uint8_t>::create_buffer((uint8_t*)unzip_data,size);
        data.size = size;
    }
    return 0;
}

int32_t ZipArchiveResource::get_resource_path(const TString &resource_path, TString &full_path)
{
    full_path = "";
    if(data_->opened_ == false){
        MR_WARN("resource zip archive not opened");
        return kErrorCodeInvalidStatus;
    }

    auto index = mz_zip_reader_locate_file(&data_->zip_archive_,resource_path.c_str(),nullptr,0);
    if(index < 0){
        MR_WARN("locate resource {} in {} failed",resource_path.c_str(),data_->zip_file_path_.c_str());
        return kErrorCodeNotExists;
    }

    TString sub_path = resource_path;
    if(resource_path[0] == std::filesystem::path::preferred_separator || resource_path[0] == '/')
        sub_path = resource_path.substr(1);
    full_path = data_->zip_file_path_ + ":" + sub_path;
    return 0;
}

int32_t DirectoryResource::open(const TString &resource_path)
{
    root_path_ = std::filesystem::path(resource_path.c_str());
    bool valid = std::filesystem::exists(root_path_);
    if(!valid){
        MR_ERROR_MORE("open resource directory faild:{}",std::filesystem::absolute(root_path_).string().c_str());
        root_path_.clear();
        return kErrorCodeInvalidArgument;
    }
    valid = std::filesystem::is_directory(root_path_);
    if(!valid){
        MR_ERROR_MORE("{} is not a directory",std::filesystem::absolute(root_path_).string().c_str());
        return kErrorCodeInvalidArgument;
    }
    return 0;
}

int32_t DirectoryResource::close()
{
    return 0;
}


int32_t DirectoryResource::get_data(const TString &resource_path, ResourceData &data)
{
    if(root_path_.empty()){
        MR_ERROR_MORE("no resource directory opened");
        return kErrorCodeInvalidStatus;
    }

    std::filesystem::path file_path = root_path_ / resource_path.c_str();
    if(!std::filesystem::exists(file_path)){
        MR_ERROR_MORE("resource file {} not exists",file_path.string().c_str());
        return kErrorCodeNotExists;
    }
    auto size = std::filesystem::file_size(file_path);

    data.data = SharedBuffer<uint8_t>::create_buffer(nullptr,size);
    data.size = size;
    FILE* file = fopen(file_path.string().c_str(),"rb");
    if(!file){
        return kErrorCodeAccessDenied;
    }

    auto ret = fread(data.data.get(),size,1,file);
    fclose(file);

    return (ret==size)?0:kErrorCodeInternalError;
}

int32_t DirectoryResource::get_resource_path(const TString &resource_path, TString &full_path)
{
    full_path = "";

    if(root_path_.empty()){
        MR_WARN("no resource directory opened");
        return kErrorCodeInvalidStatus;
    }
    std::filesystem::path file_path = root_path_ / resource_path.c_str();

    if(!std::filesystem::exists(file_path)){
        MR_WARN("file {} not exists",file_path.string().c_str());
        return kErrorCodeNotExists;
    }

    full_path = file_path.string().c_str();
    return 0;
}


ResourceStore::ResourceStore()
{

}


int32_t ResourceStore::append_resource_directory(const char *directory_path)
{
    if(providers_.find(directory_path) != providers_.end())
        return kSuccessedAlreadyExists;
    TSharedPtr<IResourceProvider> provider = TSharedPtr<IResourceProvider>(static_cast<IResourceProvider*>(new DirectoryResource()));
    auto ret = provider->open(directory_path);
    if(ret < 0){
        return ret;
    }
    providers_[directory_path] = provider;
    return kSuccessed;
}

int32_t ResourceStore::append_resource_bunble(const char *bundle_file_path)
{
    if(providers_.find(bundle_file_path) != providers_.end())
        return kSuccessedAlreadyExists;
    TSharedPtr<IResourceProvider> provider = TSharedPtr<IResourceProvider>(static_cast<IResourceProvider*>(new ZipArchiveResource()));
    auto ret = provider->open(bundle_file_path);
    if(ret < 0){
        return ret;
    }
    providers_[bundle_file_path] = provider;
    return 0;
}

int32_t ResourceStore::release_resource(const char *resource_path){
    providers_.erase(resource_path);
    return 0;
}



}//namespace vgfx
}//namespace mr

