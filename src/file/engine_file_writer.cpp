#include "Engine.h"

namespace Engine { namespace EFileWriter {
    
    void WriteScene(ERef<EScene> scene, EFile file) 
    {
        if (!scene)
        {
            std::cout << "Could not write undefined scene to file \"" << file.GetPath() << "\"" << std::endl;
            return;
        }
        EJson sceneJson = EJson::object();
        scene->SetJsObject(sceneJson);

        EString sceneJsonString = sceneJson.dump();

        ESharedBuffer sceneBuffer;
        sceneBuffer.InitWith<u8>(new u8[sceneJsonString.length() + 1], sceneJsonString.length() + 1);
        strcpy(sceneBuffer.Data<char>(), sceneJsonString.c_str());

        EFileCollection toSaveCollection = scene->GetResourceManager().GetFileCollection();

        

        toSaveCollection.AddFile("Scene.esc", sceneBuffer);
        file.SetFileBuffer(toSaveCollection.GetCompleteBuffer());
        file.SaveBufferToDisk();
    }
}}