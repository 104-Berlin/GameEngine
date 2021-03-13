#include "Engine.h"

using namespace Engine;


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

                // 
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