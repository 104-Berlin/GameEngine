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
    EJson sceneJson;

    ESharedBuffer sceneBuffer;
    if (fileCollection.GetFileAt("Scene.esc", &sceneBuffer))
    {
        if (!sceneBuffer.IsNull())
        {
            EString sceneJsonString = EString(sceneBuffer.Data<char>());
            sceneJson = EJson::parse(sceneJsonString);
        }
    }

    if (sceneJson.is_null()) 
    { 
        std::cout << "Could not Load the scene json from file \"" << file.GetPath() << "\"" << std::endl;
        return nullptr;
    }

    ERef<EScene> result = EMakeRef(EScene, "Import Scene");
    // First load all the resources
    result->GetResourceManager().LoadFileCollection(fileCollection);
    // Then load the scene data
    result->FromJsObject(sceneJson);
    
    return result;
}
