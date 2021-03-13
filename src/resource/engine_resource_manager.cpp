#include "Engine.h"

using namespace Engine;

const EVector<EResourceRegister::RegisterEntry>& EResourceRegister::GetRegisteredResourceTypes() const
{
    return fRegisteredResourceTypes;
}


void EResourceRegister::RegisterResource(const EString& name, const ESet<EString>& fileEndings, EResourceRegister::LoadFn loadFunction)
{
    RegisterEntry entry;
    entry.Name = name;
    entry.FileEndings = fileEndings;
    entry.LoadFunction = loadFunction;
    fRegisteredResourceTypes.push_back(entry);  
}

EResourceRegister& EResourceRegister::data() 
{
    static EResourceRegister instance;
    return instance;
}


EResourceManager::EResourceManager() 
    : fQueueMutex(), fIsRunning(true), fLoadingThread(std::bind(&EResourceManager::LoadingFunc, this))
{
}

EResourceManager::~EResourceManager() 
{
    fIsRunning = false;
    if (fLoadingThread.joinable())
    {
        fLoadingThread.join();
    }
}

void EResourceManager::LoadingFunc() 
{
    bool loadingQueueDidRun = false;
    while (fIsRunning)
    {
        while (fLoadingQueue.size())
        {
            loadingQueueDidRun = true;
            EString resourcePath;
            {
                std::lock_guard<std::mutex> quard(fQueueMutex);
                resourcePath = fLoadingQueue.front();
                fLoadingQueue.pop();
            }

            EFile resourceFile(resourcePath);
            if (resourceFile.Exist())
            {
                resourceFile.LoadToMemory();
                ESharedBuffer resourceBuffer = resourceFile.GetBuffer();
                // Get resource type from path ending
                EString fileEnding = resourceFile.GetFileExtension();
                for (const auto& regsiteredType : EResourceRegister::data().GetRegisteredResourceTypes())
                {
                    if (regsiteredType.FileEndings.find(fileEnding) != regsiteredType.FileEndings.end())
                    {
                        if (regsiteredType.LoadFunction)
                        {
                            // Run load function
                            ERef<EResource> loadedResource = regsiteredType.LoadFunction(resourceFile.GetFileName(), resourceBuffer);
                            fLoadedResources[resourcePath] = loadedResource;
                        }
                        break;
                    }
                }
            }
        }
        if (loadingQueueDidRun)
        {
            EApplication::gApp().QueueEvent<EResourceLoadEvent>({});
        }
        loadingQueueDidRun = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void EResourceManager::AddResourceToLoad(const EString& path) 
{
    std::lock_guard<std::mutex> guard(fQueueMutex);
    fLoadingQueue.push(path);
}

void EResourceManager::AddLoadedResource(ERef<EResource> resource) 
{
    std::lock_guard<std::mutex> loadGuard(fLoadedMutex);
    fLoadedResources[resource->GetEnginePath()] = resource;
}

EResourceManager::ResourceMap::iterator EResourceManager::begin() 
{
    return fLoadedResources.begin();
}

EResourceManager::ResourceMap::const_iterator EResourceManager::begin() const
{
    return fLoadedResources.begin();
}

EResourceManager::ResourceMap::iterator EResourceManager::end() 
{
    return fLoadedResources.end();
}

EResourceManager::ResourceMap::const_iterator EResourceManager::end() const
{
    return fLoadedResources.end();
}