#include "Engine.h"

using namespace Engine;

EResource::EResource(const EString& name, const EString& path)
    :   EObject(name),
        fFilePath(this, "FilePath"),
        fIsSaved(this, "IsSaved")
{
    fFilePath.SetValue(path);
    EFile file(path);
    if (file.GetFileExtension().compare("er"))
    {
        
    }
}

EResource::~EResource()
{

}

bool EResource::Import()
{
    return OnImport();    
}

bool EResource::OnImport()
{
    return false;
}

bool EResource::Export(const EString& filePath)
{
    return OnExport(filePath);
}

bool EResource::OnExport(const EString& filePath)
{
    return false;
}

bool EResource::Save()
{
    fIsSaved.SetValue(OnSave());
    return fIsSaved.GetValue();
}

bool EResource::OnSave()
{
    return false;
}

bool EResource::Load()
{
    return OnLoad();
}

bool EResource::OnLoad()
{
    return false;
}
