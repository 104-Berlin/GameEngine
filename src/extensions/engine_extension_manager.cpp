#include "Engine.h"

using namespace Engine;

EExtension::EExtension(const EString& pluginName) 
{
    EFolder pluginFolder(EBaseFolder::PLUGIN);
    EFile pluginFile(pluginFolder.GetFullPath() + pluginName + ".epl");

    if (!pluginFile.Exist())
    {
        std::cout << "Plugin file \"" << pluginName << "\" does not exist!" << std::endl;
        return;
    }

    LoadPlugin(pluginFile.GetFullPath());
    auto loadFunction = (void(*)(EExtensionInitializer&))GetFunction("LoadExtension");
    if (loadFunction)
    {
        EExtensionInitializer init = { EPanelComponentData::data() };
        
        std::cout << "Running load function for plugin \"" << pluginName << "\"\n";
        loadFunction(init);

    }
}

EExtension::~EExtension() 
{
    #ifdef EWIN
    FreeLibrary(fHandle);
    #else
    dlclose(fHandle);
    #endif
}

void EExtension::LoadPlugin(const EString& fullPath) 
{   
#ifdef EWIN
    fHandle = LoadLibrary(TEXT(fullPath.c_str()));
#else
    fHandle = dlopen(fullPath.c_str(), RTLD_LAZY);
    if (!fHandle) 
    {
        std::cout << "Could not load plugin \"" << fullPath << "\"!" << std::endl;
    }
    
#endif
}

void* EExtension::GetFunction(const EString& functionName) 
{
#ifdef EWIN
    return GetProcAddress(fHandle, functionName.c_str());
#else
    void* result = dlsym(fHandle, functionName.c_str());
    return result;
#endif
}

void EExtension::InitImGui(ImGuiContext* context) 
{
    auto loadFunction = (void(*)(ImGuiContext*))GetFunction("InitImGui");
    if (loadFunction)
    {
        loadFunction(context);
    }
}

EExtensionManager::EExtensionManager() 
{
    
}

EExtensionManager::~EExtensionManager() 
{
}

void EExtensionManager::LoadPluginFolder() 
{
    EFolder pluginFolder(EBaseFolder::PLUGIN, "", EFolderOptions_CreateIfNotExist);
    for (const auto file : pluginFolder.Iterator())
    {
        EFile e_file(file.path().string());
        fLoadedExtensions.push_back(new EExtension(e_file.GetFileName()));
    }

    EVector<EExtension*> extensions = GetLoadedExtensions();
    IN_RENDER1(extensions, {
        for (EExtension* ext : extensions)
        {
            // TODO: Make ui work for extensions again
            //ext->InitImGui(UI::GetContext());
        }
    })
}

void EExtensionManager::UnLoadExtensions() 
{
    for (EExtension* extension : fLoadedExtensions)
    {
        delete extension;
    }   
    fLoadedExtensions.clear();
}

const EVector<EExtension*>& EExtensionManager::GetLoadedExtensions() 
{
    return fLoadedExtensions;
}