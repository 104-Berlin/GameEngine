#pragma once




#define PANEL_NAME_COMPONENT "Components"
#define PANEL_NAME_SCENETREE "Scene Tree"
#define PANEL_NAME_RESOURCES "Resources"

namespace Engine {

    struct ComponentDescription
    {
        using Callback = std::function<void(EObject)>;
        using FieldsUIFn = std::function<ERef<EUIField>(EObject)>;
        using HasFn = std::function<bool(EObject)>;

        EString Name;
        FieldsUIFn CreateUIField;
        HasFn Has;
        Callback Create;
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
            
            newComponentDsc->CreateUIField = [newComponentDsc](EObject object) -> ERef<EUIField> {
                ERef<EUIContainer> result = EMakeRef(EUIContainer, newComponentDsc->Name);
                result->SetShow();
                if (object.HasComponent<T>())
                {
                    object.GetComponent<T>()._reflect([result](const char* name, auto property){
                        result->AddChild(UI::CreateInputField<decltype(property)>(name, property));
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

            sComponentDescriptions.push_back(newComponentDsc);
        }

        void ClearComponentData();

        static EPanelComponentData& data();

    };


    namespace ApplicationPanels {
        void CreateDefaultApplicationPanels();
        void CreateDefaultMainMenuBar();
    }
}