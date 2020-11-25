#pragma once

namespace Engine {

    class EObject
    {
    private:
        EUUID fUuid;
        EProperty<EString>  fName;

        EMap<EString, EBaseProperty*> fAllProperties; 
    public:
        EObject(const EString& name, const EUUID& uuid = EUUID().CreateNew());

        void FromJsObject(const EJson& ref);
        void SetJsObject(EJson& ref) const;  

        virtual void OnFromJsObject(const EJson& ref);
        virtual void OnSetJsObject(EJson& ref) const;

        void AddProperty(EBaseProperty* prop);
        EBaseProperty* GetPropertyByName(const EString& name);
        const EBaseProperty* GetPropertyByName(const EString& name) const;
    };

}