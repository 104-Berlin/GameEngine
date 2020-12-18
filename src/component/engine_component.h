#pragma once

namespace Engine {

    struct EUUIDComponent
    {
        REFLACTABLE(
            (EUUID, UUID)
        )
        
        EUUIDComponent(const EUUIDComponent&) = default;
        EUUIDComponent(const EUUID& uuid)
            : UUID(uuid)
        {}
        
    };

    struct ENameComponent
    {
        REFLACTABLE(
            (EString, Name)
        )
        
        ENameComponent()
            : Name("Unknown")
        {}
        ENameComponent(const ENameComponent&) = default;

        ENameComponent(const EString& name)
            : Name(name)
        {}
    };

    struct EMeshComponent
    {
        REFLACTABLE(
            (ERef<EMesh>, Mesh)
        )

        EMeshComponent() = default;
        EMeshComponent(const EMeshComponent&) = default;

    };

}