#pragma once

namespace Engine {

    struct EObject;
    class EComponentPanel;

    E_API class EScene
    {
        using ObjectCallback = std::function<void(EObject)>;
    private:
        EProperty<EString>                              fName;
        EObjectRef                                      fSelectedObject;


        // Entities
        entt::registry                                  fRegistry;
        EUnorderedMap<EUUID, EObject, UuidHash>         fEntityMap;
    public:
        EScene(const EString& name);
        ~EScene();

        EObject CreateObject();

        void Update(float delta);

        EObjectRef& GetSelectedObject();

        EObject GetObjectByUuid(const EUUID& uuid);

        void SetJsObject(EJson& json);
        void FromJsObject(const EJson& json);

        // Looping functions
        void Clear();
        void ForEachObject(ObjectCallback fn);


        template <typename ...Component>
        auto view()
        {
            return fRegistry.view<Component...>();
        }
    public:
        friend class EObject;
    private:
        void CallObjectFunc(EEntity entity, ObjectCallback fn);
    };

}