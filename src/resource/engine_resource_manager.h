#pragma once

namespace Engine {

    class E_API EResourceRegister
    {
    public:
        using LoadFn = std::function<ERef<EResource>(EString, ESharedBuffer)>;

        struct RegisterEntry
        {
            EString         Name;
            ESet<EString>   FileEndings;
            LoadFn          LoadFunction;
        };
    private:
        EVector<RegisterEntry> fRegisteredResourceTypes;
    public:
        const EVector<RegisterEntry>& GetRegisteredResourceTypes() const;
        void RegisterResource(const EString& name, const ESet<EString>& fileEndings, LoadFn loadFunction);

        static EResourceRegister& data();
    };



    struct E_API EResourceLoadEvent
    {

    };

    class E_API EResourceManager
    {
        using ResourceMap = EUnorderedMap<EString, ERef<EResource>>;
        using WorkFinishedFunction = std::function<void()>;
    private:
        ResourceMap                 fLoadedResources;
        EFileCollection             fFileCollections;

        std::mutex                  fLoadedMutex;

        std::queue<EString>         fLoadingQueue;
        std::mutex                  fQueueMutex;
        std::thread                 fLoadingThread;

        std::atomic<bool>           fIsRunning;
    public:
        EResourceManager();
        ~EResourceManager();

        void LoadingFunc();

        void AddResourceToLoad(const EString& path);
        void LoadFileCollection(const EFileCollection& fileCollection);
        ERef<EResource> AddLoadedResource(ERef<EResource> resource);

        const EFileCollection& GetFileCollection() const;

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