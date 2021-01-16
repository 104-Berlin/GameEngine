#pragma once

namespace Engine {

    class EExtension
    {
    public:
        EExtension(const EString& pluginName);
    private:
        void    LoadPlugin(const EString& fullPath);
        void*   GetFunction(const EString& functionName);
    private:
#ifdef EWIN
        HINSTANCE fHandle;
#else
        void* fHandle;
#endif
    };

    class EExtensionManager
    {
    public:
        EExtensionManager();
        
    };

}