#pragma once

namespace Engine {

    class EObject
    {
    public:
        EObject(const EUUID& uuid = EUUID().CreateNew());
        virtual ~EObject() = default;

        void FromJsObject(const EJson& ref);
        void SetJsObject(EJson& ref) const;  

        virtual void OnFromJsObject(const EJson& ref);
        virtual void OnSetJsObject(EJson& ref) const;
    };

}