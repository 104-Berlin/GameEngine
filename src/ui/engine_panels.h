#pragma once

namespace Engine {

    typedef std::function<void(const char*, EBaseProperty*)> EReflectFn;

    struct ComponentDescription
    {
        EString Name;

        void Reflect(EObject entity, EReflectFn reflectFunction)
        {
            OnReflect(entity, reflectFunction);
        }

        bool Has(EObject entity)
        {
            return OnHas(entity);
        }

        virtual bool OnHas(EObject entity) = 0;
        virtual void OnReflect(EObject entity, EReflectFn relfectFn) = 0;
    protected:
        ComponentDescription() : Name("EMPTY") {}
    };

#define REGISTER_COMPONENT(type) struct CONCATENATE(type, __Description) : public ComponentDescription {\
                                        CONCATENATE(type, __Description)()\
                                        {\
                                            this->Name = #type;\
                                        }\
                                        virtual void OnReflect(EObject entity, EReflectFn reflectFn)\
                                        {\
                                            if (entity.HasComponent<type>())\
                                            {\
                                                entity.GetComponent<type>()._reflect(reflectFn);\
                                            }\
                                        }\
                                        virtual bool OnHas(EObject entity)\
                                        {\
                                            return entity.HasComponent<type>();\
                                        }\
                                    };\
                                    EPanelComponentData::AddComponentDescription(new CONCATENATE(type, __Description)());



    class EPanelComponentData
    {
    private:
        static EVector<ComponentDescription*> sComponentDescriptions;
    public:
        static void AddComponentDescription(ComponentDescription* dsc);
        static const EVector<ComponentDescription*>& GetComponentDescription();
    };

    class EComponentPanel : public EUIPanel
    {
    public:
        EComponentPanel();

        void SetObjectToDisplay(EObject object);
    };

}