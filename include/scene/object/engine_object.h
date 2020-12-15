#pragma once

namespace Engine {

    class EObject
    {
    private:
        
    public:
        EObject();
        virtual ~EObject() = default;

        void FromJsObject(const EJson& ref);
        void SetJsObject(EJson& ref) const;  

        virtual void OnFromJsObject(const EJson& ref);
        virtual void OnSetJsObject(EJson& ref) const;
    };

}