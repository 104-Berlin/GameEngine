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
    EString result = GetFilePath();
    size_t rootDirEnd = result.find_first_of(ROOT_RES_DIR);
    return result.substr(rootDirEnd, result.length() - rootDirEnd);
}

bool EResource::Load() 
{
    return OnLoad();
}

bool EResource::OnLoad() 
{
    return false;
}
