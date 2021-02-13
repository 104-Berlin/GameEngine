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
        EObjectRef                          fSelectedObject;


        // Entities
        entt::registry                      fRegistry;
    public:
        EScene(const EString& name);
        ~EScene();

        EObject CreateObject();

        void Update(float delta);

        EObjectRef& GetSelectedObject();

        void SetJsObject(EJson& json);
        void FromJsObject(const EJson& json);

        // Looping functions
        void ForEachObject(ObjectCallback fn);
    public:
        friend class EObject;
    };

}