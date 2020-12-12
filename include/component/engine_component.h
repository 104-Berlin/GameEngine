#pragma once

namespace Engine {

    class EComponent : public EObject
    {
    public:
        EObject*    AttachedObject;
    public:
        EComponent();
        virtual ~EComponent() = default;
    };

}