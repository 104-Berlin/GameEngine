#include "Engine.h"

using namespace Engine;

EFolder::EFolder(const EString& path) 
{
    fFullPath = path;
}

EFolder::EFolder(EBaseFolder f, const EString& path) 
{
    fFullPath = GetBaseFolderPath(f) + path;    
}

const EString& EFolder::GetFullPath() const
{
    return fFullPath;
}

bool EFolder::Exist() const
{
    return std::filesystem::exists(fFullPath);
}

std::filesystem::directory_iterator EFolder::Iterator()  const
{
    return std::filesystem::directory_iterator(GetFullPath());    
}

EString EFolder::GetBaseFolderPath(EBaseFolder f) 
{
    EString result = "";
    switch(f)
    {
    case EBaseFolder::APPLICATION:  result = std::filesystem::current_path(); break;
    case EBaseFolder::PLUGIN:       result = std::filesystem::absolute(std::filesystem::path("plugins/")).lexically_normal(); break;
    case EBaseFolder::RES:          result = std::filesystem::absolute(std::filesystem::path("res/")).lexically_normal(); break;
    }
    return result;
}