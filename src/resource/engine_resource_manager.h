#pragma once

namespace Engine {

    struct EResourceLoadEvent
    {

    };

    class E_API EResourceManager
    {
        using ResourceMap = EUnorderedMap<EString, ERef<EResource>>;
        using WorkFinishedFunction = std::function<void()>;
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

        void LoadingFunc();

        template <typename T>
        ERef<T> GetResource(const EString& fileIdent)
        {
            std::lock_guard<std::mutex> guard(fLoadedMutex);
            if (fLoadedResources.find(fileIdent) != fLoadedResources.end())
            {
                return std::static_pointer_cast<T>(fLoadedResources.at(fileIdent));
            }
            return nullptr;
        }

        ResourceMap::iterator begin();
        ResourceMap::const_iterator begin() const;
        ResourceMap::iterator end();
        ResourceMap::const_iterator end() const;
    };
    

}