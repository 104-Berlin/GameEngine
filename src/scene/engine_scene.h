#pragma once

namespace Engine {

    struct EObject;
    class EComponentPanel;

    class EScene
    {
        using ObjectCallback = std::function<void(EObject)>;
    private:
        EString                             fName;
        EObjectRef                          fSelectedObject;


        // Entities
        entt::registry                      fRegistry;
    public:
        EScene(const EString& name);
        ~EScene();

        EObject CreateObject();

        void Update(float delta);

        EObjectRef& GetSelectedObject();


        // Looping functions
        void ForEachObject(ObjectCallback fn);
    public:
        friend class EObject;
    };

}