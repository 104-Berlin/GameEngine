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
    auto loadFunction = (void(*)())dlsym(fHandle, "LoadExtension");
    if (loadFunction)
    {
        std::cout << "Running load function\n";
        loadFunction();
    }
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

EExtensionManager::EExtensionManager() 
{
    
}

EExtensionManager::~EExtensionManager() 
{
    for (EExtension* extension : fLoadedExtensions)
    {
        delete extension;
    }
    fLoadedExtensions.clear();
}

void EExtensionManager::LoadPluginFolder() 
{
    EFolder pluginFolder(EBaseFolder::PLUGIN);
    for (const auto file : pluginFolder.Iterator())
    {
        EFile e_file(file.path());
        fLoadedExtensions.push_back(new EExtension(e_file.GetFileName()));
    }
}