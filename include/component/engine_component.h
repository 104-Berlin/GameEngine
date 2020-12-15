#pragma once

namespace Engine {

    struct EUUIDComponent
    {
        EUUID UUID;
        EUUIDComponent(const EUUIDComponent&) = default;
        EUUIDComponent(const EUUID& uuid)
            : UUID(uuid)
        {}
        
    };

    struct ENameComponent
    {
        EString Name = "";
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
        
    };

}