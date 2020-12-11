#pragma once

namespace Engine {

    class EObject
    {
    private:
        EMap<EString, EBaseProperty*> fAllProperties; 



        EUUID fUuid;
        EProperty<EString>  fName;
    public:
        EObject(const EString& name, const EUUID& uuid = EUUID().CreateNew());

        void FromJsObject(const EJson& ref);
        void SetJsObject(EJson& ref) const;  

        virtual void OnFromJsObject(const EJson& ref);
        virtual void OnSetJsObject(EJson& ref) const;

        void AddProperty(EBaseProperty* prop);
        EBaseProperty* GetPropertyByName(const EString& name);
        const EBaseProperty* GetPropertyByName(const EString& name) const;

        void SetName(const EString& name);
        const EString& GetName() const;
        const EUUID& GetUuid() const;

        void Render();
        virtual void OnRender();
        void Update(float delta);
        virtual void OnUpdate(float delta);
        void RenderUI();
        virtual void OnRenderUI();

    };

}