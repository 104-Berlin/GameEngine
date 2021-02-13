#pragma once

namespace Engine {

    struct EObject;
    class EComponentPanel;

    class EScene
    {
        using ObjectCallback = std::function<void(EObject)>;
    private:
        EProperty<EString>                  fName;
        EObjectRef                          fSelectedObject;


        // Entities
        entt::registry                      fRegistry;
        EUnorderedMap<EUUID, EObject, UuidHash>       fEntityMap;
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
        void ForEachObject(ObjectCallback fn);
    public:
        friend class EObject;
    };

}