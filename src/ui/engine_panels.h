#pragma once

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

            sComponentDescriptions.push_back(newComponentDsc);
        }

        void ClearComponentData();

        static EPanelComponentData& data();

    };

    class EComponentPanel : public EUIPanel
    {
    private:
        EObject fActiveObject;
    public:
        EComponentPanel();

        void SetObjectToDisplay(EObject object);

        virtual bool OnRender() override;
    private:
        void UpdateComponents();
    };

}