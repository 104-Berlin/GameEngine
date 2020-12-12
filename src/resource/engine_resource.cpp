#include "Engine.h"

using namespace Engine;

EResource::EResource(const EString& name, const EString& path)
    :   EObject(name),
        fFilePath(this, "FilePath"),
        fIsSaved(this, "IsSaved")
{
    fFilePath.SetValue(path);
    EFile file(path);
    if (path.empty() || file.GetFileExtension().compare("er"))
    {
        this->Load();
    }
    else
    {
        this->Import();
    }
}

EResource::~EResource()
{

}

const EString& EResource::GetFilePath() const
{
    return fFilePath.GetValue();
}

bool EResource::Import()
{
    return this->OnImport();    
}

bool EResource::OnImport()
{
    return false;
}

bool EResource::Export(const EString& filePath)
{
    return this->OnExport(filePath);
}

bool EResource::OnExport(const EString& filePath)
{
    return false;
}

bool EResource::Save()
{
    fIsSaved.SetValue(this->OnSave());
    return fIsSaved.GetValue();
}

bool EResource::OnSave()
{
    return false;
}

bool EResource::Load()
{
    bool result = this->OnLoad();
    return result;
}

bool EResource::OnLoad()
{
    return false;
}
