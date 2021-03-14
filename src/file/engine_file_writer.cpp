#include "Engine.h"

namespace Engine { namespace EFileWriter {
    
    void WriteScene(ERef<EScene> scene, EFile file) 
    {
        if (!scene)
        {
            std::cout << "Could not write undefined scene to file \"" << file.GetPath() << "\"" << std::endl;
            return;
        }
        //EJson sceneJson = EJson::object();
        //scene->SetJsObject(sceneJson);
        //file.SetFileAsString(sceneJson.dump());
        file.SetFileBuffer(scene->GetResourceManager().GetFileCollection().GetCompleteBuffer());
        file.SaveBufferToDisk();
    }
}}