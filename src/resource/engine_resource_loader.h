#pragma once

namespace Engine {

    class EResourceLoaderBase
    {
    protected:
        EResourceLoaderBase();
    };

    template <typename ResourceType>
    class EResourceLoader : private EResourceLoaderBase
    {
    public:

    };

}