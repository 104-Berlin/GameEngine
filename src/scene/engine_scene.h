#pragma once

namespace Engine {

    class EScene
    {
    private:
        EString                             fName;
        EEntity                             fSelectionContext;


        // TEMP
        ERef<EFrameBuffer>                  fSceneFrameBuffer;
        float                               fViewPortWidth;
        float                               fViewPortHeight;

        // Entities
        entt::registry                      fRegistry;
    public:
        EScene(const EString& name);
        ~EScene();

        EObject CreateObject();

        void Render();
        void RenderUI();
        void Update(float delta);

        //TEMP
        ERef<EFrameBuffer> GetFrameBuffer(){ return fSceneFrameBuffer;}
    public:
        friend class EObject;
    };

}