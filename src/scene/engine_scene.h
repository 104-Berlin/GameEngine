#pragma once

namespace Engine {

    struct EObject;
    class EComponentPanel;

    class EScene
    {
    private:
        EString                             fName;
        EEntity                             fSelectionContext;


        // TEMP
        float                               fViewPortWidth;
        float                               fViewPortHeight;
        EComponentPanel*                    fComponentPanel;
        //ERef<EFrameBuffer>                  fSceneFrameBuffer;

        // Entities
        entt::registry                      fRegistry;
    public:
        EScene(const EString& name);
        ~EScene();

        EObject CreateObject();

        void Render();
        void RenderUI();
        void Update(float delta);
    public:
        friend class EObject;
    };

}