#pragma once

namespace Engine {

    class EObject
    {
    private:
        EScene*    fScene;
        EEntity             fHandle;
    public:
        EObject(EEntity handle, EScene* scene);
        virtual ~EObject() = default;

        // Wrapper functions
        template <typename T, typename... Args>
        T& AddComponent(Args&&... args)
        {
            return fScene->fRegistry.emplace<T>(fHandle, std::forward<Args>(args)...);
        }

        template <typename T>
        bool HasComponent()
        {
            return fScene->fRegistry.has<T>(fHandle);
        }

        template <typename T>
        T& GetComponent()
        {
            return fScene->fRegistry.get<T>(fHandle);   
        }

        void Delete()
        {
            fScene->fRegistry.destroy(fHandle);
        }       

        void FromJsObject(const EJson& ref);
        void SetJsObject(EJson& ref) const;  

        virtual void OnFromJsObject(const EJson& ref);
        virtual void OnSetJsObject(EJson& ref) const;
    };

}