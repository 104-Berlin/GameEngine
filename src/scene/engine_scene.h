#pragma once

namespace Engine {

    struct EObject;
    class EComponentPanel;

    class EObjectReference : public EBaseProperty
    {
    private:
        EObject* fObject;
    public:
        EObjectReference(const EString& refName);
        ~EObjectReference();
        
        void SetValue(EObject object);
        EObject GetValue();

        virtual void OnFromJsObject(const EJson& ref);
        virtual void OnSetJsObject(EJson& ref) const;
    };

    class EScene
    {
        using ObjectCallback = std::function<void(EObject)>;
    private:
        EProperty<EString>                  fName;

        EObjectReference                    fSelectedObject;


        // TEMP
        float                               fViewPortWidth;
        float                               fViewPortHeight;
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

        EObjectReference& GetSelectedObject();

        void SetJsObject(EJson& json);
        void FromJsObject(const EJson& json);

        // Looping functions
        void ForEachObject(ObjectCallback fn);
    public:
        friend class EObject;
    };

}