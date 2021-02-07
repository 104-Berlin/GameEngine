#pragma once

namespace Engine {

    struct ComponentDescription
    {
        using Callback = std::function<void(EObject)>;
        using FieldsUIFn = std::function<ERef<EUIField>(EObject)>;
        using HasFn = std::function<bool(EObject)>;
        using SetJsFn = std::function<void(EObject, EJson&)>;
        using FromJsFn = std::function<void(EObject, const EJson&)>;

        EString     Name;
        FieldsUIFn  CreateUIField;
        HasFn       Has;
        Callback    Create;
        SetJsFn     SetJsObject;
        FromJsFn    FromJsObject;
    };
 


    class EPanelComponentData
    {
    private:
        EVector<ComponentDescription*> sComponentDescriptions;
    public:
        ~EPanelComponentData();

        void AddComponentDescription(ComponentDescription* dsc);
        const EVector<ComponentDescription*>& GetComponentDescription();

        template <typename T>
        void RegisterComponent(const EString& componentName)
        {
            ComponentDescription* newComponentDsc = new ComponentDescription();
            newComponentDsc->Name = componentName;
            
            newComponentDsc->CreateUIField = [newComponentDsc](EObject object) -> ERef<EComponentContainer> {
                ERef<EComponentContainer> result = EMakeRef(EComponentContainer, newComponentDsc->Name);
                if (object.HasComponent<T>())
                {
                    object.GetComponent<T>()._reflect([result](const char* name, auto property){
                        ERef<EInputField<decltype(property)>> inputField = EMakeRef(EInputField<decltype(property)>, property);
                        result->AddChild(inputField);
                    });
                }
                return result;
            };

            newComponentDsc->Has = [](EObject object) -> bool {
                return object.HasComponent<T>();
            };

            newComponentDsc->Create = [](EObject object) {
                object.AddComponent<T>();
            };

            newComponentDsc->SetJsObject = [componentName](EObject object, EJson& json){
                if (object.HasComponent<T>())
                {
                    object.GetComponent<T>()._reflect([&json](const char* name,auto property){
                        property->SetJsObject(json);
                    });
                }
            };

            newComponentDsc->FromJsObject = [componentName](EObject object, const EJson& json){
                if (JSHelper::HasParam(json, componentName))
                {
                    if (!object.HasComponent<T>())
                    {
                        object.AddComponent<T>();
                    }
                    T& component = object.GetComponent<T>();
                    component._reflect([&json](const char* name,auto property){
                        property->FromJsObject(json);
                    });
                }
            };

            sComponentDescriptions.push_back(newComponentDsc);
        }

        void ClearComponentData();

        static EPanelComponentData& data();

    };
}