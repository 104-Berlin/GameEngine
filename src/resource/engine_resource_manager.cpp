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

void EResourceManager::LoadAllFromFolder(const EFolder& folder) 
{
    if (!folder.Exist()) { return; }    

    for (auto& p : folder.Iterator())
    {
        std::cout << "Adding " << p.path() << " to loading queue width type: " << GetResourceTypeFromFile(p.path()) << std::endl;
        std::lock_guard<std::mutex> quard(fQueueMutex);
        fLoadingQueue.push(p.path().lexically_normal());
    }
}

void EResourceManager::LoadingFunc() 
{
    while (fIsRunning)
    {
        while (fLoadingQueue.size())
        {
            EString resourcePath;
            {
                std::lock_guard<std::mutex> quard(fQueueMutex);
                resourcePath = fLoadingQueue.front();
                fLoadingQueue.pop();
            }
            EString resourceType = GetResourceTypeFromFile(resourcePath);
            // throw error when resource type "UNKOWN"

            ERef<EResource> newResource = nullptr;
            if (resourceType == typeid(ETexture2D).name())
            {
                newResource = ETexture2D::Create(resourcePath);
            }
            else if (resourceType == typeid(EShader).name())
            {
                newResource = EShader::Create(resourcePath);
            }
            else if (resourceType == typeid(EMesh).name())
            {
                newResource = EMakeRef(EMesh, resourcePath);
            }

            // Add resource to array
            if (newResource && newResource->Load())
            {
                AddLoadedResource(newResource);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void EResourceManager::AddLoadedResource(ERef<EResource> resource) 
{
    std::lock_guard<std::mutex> guard(fLoadedMutex);
    std::cout << "Finished loading resource \"" << resource->GetNameIdent() << "\"" << std::endl;
    fLoadedResources[resource->GetNameIdent()] = resource;
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

EString EResourceManager::GetResourceTypeFromFile(const EString& filePath) 
{
    EFile file(filePath);

    if (file.HasExtension("rc")) // Own Engine resource format. Read type from that
    {
        // This file should be json format. So just parse it and get the resource type
        EString fileContent = file.GetFileAsString();
        EJson fileJson = EJson::parse(fileContent);
        if (!fileJson.is_null())
        {
            // The json is loaded correctly
            if (JSHelper::HasParam(fileJson, "ResourceType"))
            {
                EString resultType;
                JSHelper::ConvertObject(fileJson, &resultType);
                return resultType;
            }
        }
    }
    else    // Get the file type from the extions
    {
        if (file.HasExtension("jpeg", "png", "bmp", "tga"))
        {
            return typeid(ETexture2D).name();
        }
        else if (file.HasExtension("shader"))
        {
            return typeid(EShader).name();
        }
        else if (file.HasExtension("fbx", "obj"))
        {
            return typeid(EMesh).name();
        }
    }
    return "UNKNOWN";
}
