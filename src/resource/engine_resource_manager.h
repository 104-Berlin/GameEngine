#pragma once

namespace Engine {

    class EResourceManager
    {
    private:
        EVector<ERef<EResource>>    fLoadedResources;
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

        EVector<ERef<EResource>>::iterator begin();
        EVector<ERef<EResource>>::const_iterator begin() const;
        EVector<ERef<EResource>>::iterator end();
        EVector<ERef<EResource>>::const_iterator end() const;

        static EString GetResourceTypeFromFile(const EString& filePath);
    };
    

}