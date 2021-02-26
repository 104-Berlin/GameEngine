#pragma once

namespace Engine {
    struct EExtensionInitializer
    {
        // A registry of funtions to call to register components or something
        EPanelComponentData& componentData;
        EUIManager&          uiManager;
    };

    class E_API EExtension
    {
    public:
        EExtension(const EString& pluginName);
        ~EExtension();
    private:
        void    LoadPlugin(const EString& fullPath);
        void*   GetFunction(const EString& functionName);
    public:
        void InitImGui();
    private:
#ifdef EWIN
        HINSTANCE fHandle;
#else
        void* fHandle;
#endif
    };

    class E_API EExtensionManager
    {
    private:
        EVector<EExtension*> fLoadedExtensions;
    public:
        EExtensionManager();
        ~EExtensionManager();
        
        void LoadPluginFolder();
        void UnLoadExtensions();
        
        const EVector<EExtension*>& GetLoadedExtensions();
    };

}