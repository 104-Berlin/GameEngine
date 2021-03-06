#include "Engine.h"


using namespace Engine;

#ifdef EWIN
#define ROOT_RES_DIR "res\\"
#else
#define ROOT_RES_DIR "res/"
#endif

EResource::EResource(const EString& path) 
    : fFile(path), fEngineDir()
{
    if (fFile.GetFileExtension().empty())
    {
        fFile = EFile(path + ".rc");
    }
}

void EResource::SetEngineDirectory(const EString& path) 
{
    fEngineDir = path;
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
    return GetName() + "." + fFile.GetFileExtension();
}

EString EResource::GetEnginePath() const
{
    return fEngineDir + GetNameIdent();
}