#pragma once

namespace Engine {

    class EObject
    {
    private:
        EScene*             fScene = nullptr;
        EEntity             fHandle = entt::null;
    public:
        EObject() = default;
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

        bool HasComponentRuntime(entt::id_type type)
        {
            std::vector<entt::id_type> types = {type};
            entt::basic_runtime_view runtimeView = fScene->fRegistry.runtime_view(std::cbegin(types), std::cend(types));
            return runtimeView.contains(fHandle);
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

        operator bool () const
        {
            return fHandle != entt::null && fScene;
        }

        void FromJsObject(const EJson& ref);
        void SetJsObject(EJson& ref) const;  

        virtual void OnFromJsObject(const EJson& ref);
        virtual void OnSetJsObject(EJson& ref) const;
    };

}