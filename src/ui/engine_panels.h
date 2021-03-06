#pragma once


#define PANEL_NAME_COMPONENT "Components"
#define PANEL_NAME_SCENETREE "Scene Tree"
#define PANEL_NAME_RESOURCES "Resources"
#define PANEL_NAME_VIEWPORT "Viewport"

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
    
    struct EComponentsChangedEvent
    {
        EVector<ComponentDescription*> Descriptions;
    };
    class E_API EPanelComponentData
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
            std::cout << "Registering Component " << componentName << std::endl;
            ComponentDescription* newComponentDsc = new ComponentDescription();
            newComponentDsc->Name = componentName;
            
            newComponentDsc->CreateUIField = [newComponentDsc](EObject object) -> ERef<EUIField> {
                ERef<EUIContainer> result = EMakeRef(EUIContainer, newComponentDsc->Name);
                result->SetShow();
                if (object.HasComponent<T>())
                {
                    object.GetComponent<T>()._reflect([result](const char* name, auto property){
                        result->AddChild(UI::CreateInputField<decltype(property)>(name, property));
                    });
                }
                return std::dynamic_pointer_cast<EUIField>(result);
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
                if (object.HasComponent<T>())
                {
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
    private:
        void SendEvent();
    };


    namespace ApplicationPanels {
        E_API void CreateDefaultApplicationPanels();
        E_API void CreateDefaultMainMenuBar();
    }
}
