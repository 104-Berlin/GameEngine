#include "Engine.h"


using namespace Engine;

#ifdef EWIN
#define ROOT_RES_DIR "res\\"
#else
#define ROOT_RES_DIR "res/"
#endif

EResource::EResource(const EString& path) 
    : fFile(path)
{
    
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
    size_t rootDirEnd = result.find(ROOT_RES_DIR);
    if (rootDirEnd != EString::npos)
    {
        return result.substr(rootDirEnd + std::strlen(ROOT_RES_DIR), result.length() - (rootDirEnd + std::strlen(ROOT_RES_DIR)));
    }
    else
    {
        return result;
    }
}

bool EResource::Load() 
{
    return OnLoad();
}

bool EResource::OnLoad() 
{
    return false;
}
