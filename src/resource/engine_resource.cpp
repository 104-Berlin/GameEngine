#include "Engine.h"


using namespace Engine;

#define ROOT_RES_DIR "res/"

EResource::EResource(const EString& path) 
    : fFile(ROOT_RES_DIR + path)
{
    Load();
}

EString EResource::GetFilePath() const
{
    return fFile.GetFullPath();
}

const EString& EResource::GetName() const
{
    return fFile.GetFileName();
}

EString EResource::GetNameIdent() const
{
    EString result = fFile.GetPath();
    size_t root_dir_len = EString(ROOT_RES_DIR).length();
    return result.substr(root_dir_len, result.length() - (fFile.GetFileExtension().length() + root_dir_len + 1));
}

bool EResource::Load() 
{
    return OnLoad();
}

bool EResource::OnLoad() 
{
    return false;
}
