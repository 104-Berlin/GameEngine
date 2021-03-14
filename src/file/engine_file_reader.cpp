#include "Engine.h"

using namespace Engine;

ERef<EScene> EFileReader::ReadScene(EFile file) 
{
    if (!file.Exist())
    {   
        std::cout << "Could not find Scene file \"" << file.GetPath() << "\"!" << std::endl;
        return nullptr;
    }
    //EString fileAsString = file.GetFileAsString();
    //EJson fileJson = EJson::parse(fileAsString);
    //if (fileJson.is_null()) 
    //{
    //    std::cout << "File is not a valid json format" << std::endl;
    //    return nullptr;
    //}
    //ERef<EScene> result = EMakeRef(EScene, "ImportScene");
    //result->FromJsObject(fileJson);
    //return result;
    file.LoadToMemory();
    ESharedBuffer fileBuffer = file.GetBuffer();
    EFileCollection fileCollection;
    fileCollection.SetFromCompleteBuffer(fileBuffer);


    ERef<EScene> result = EMakeRef(EScene, "Import Scene");
    result->GetResourceManager().LoadFileCollection(fileCollection);
    return result;
}
