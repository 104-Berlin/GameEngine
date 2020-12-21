#pragma once

namespace Engine {

    class EResourceManager
    {
        using ResourceMap = EUnorderedMap<EString, ERef<EResource>>;
    private:
        ResourceMap                 fLoadedResources;
        std::mutex                  fLoadedMutex;

        std::queue<EString>         fLoadingQueue;
        std::mutex                  fQueueMutex;
        std::thread                 fLoadingThread;

        std::atomic<bool>           fIsRunning;
    public:
        EResourceManager();
        ~EResourceManager();

        void LoadAllFromFolder(const EFolder& folder);

        void LoadingFunc();
        void AddLoadedResource(ERef<EResource> resource);

        template <typename T>
        ERef<T> GetResource(const EString& fileIdent)
        {
            std::lock_guard<std::mutex> guard(fLoadedMutex);
            return std::static_pointer_cast<T>(fLoadedResources.at(fileIdent));
        }

        ResourceMap::iterator begin();
        ResourceMap::const_iterator begin() const;
        ResourceMap::iterator end();
        ResourceMap::const_iterator end() const;

        static EString GetResourceTypeFromFile(const EString& filePath);
    };
    

}