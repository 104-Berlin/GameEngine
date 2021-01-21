#pragma once

namespace Engine
{
    static i32 next_ui_id()
    {
        static i32 currentUiId = 0;
        return ++currentUiId; 
    }

    class EUIField
    {
    protected:
        EVector<ERef<EUIField>>         fChildren;
        i32                             fId;
    public:
        EUIField();

        virtual const EString& GetDisplayName() const = 0;

        void Render();

        /**
         * @return wether or not the chidren should be rendered. Default is true
         * */
        virtual bool OnRender();
        virtual void OnRenderEnd();

        ERef<EUIField> AddChild(const ERef<EUIField>& child);
        void ClearChildren();
    };

    class EUIPanel : public EUIField
    {
    private:
        EString         fName;
        bool            fOpen;
    public:
        EUIPanel(const EString& panelName);

        virtual const EString& GetDisplayName() const override;

        virtual bool OnRender() override;
        virtual void OnRenderEnd() override;
    protected:
    };


    class EInputField : public EUIField
    {
    private:
        EBaseProperty* fProperty;
    public:
        EInputField(EBaseProperty* property);

        virtual const EString& GetDisplayName() const override;

        virtual bool OnRender() override;
    };

    class EComponentContainer : public EUIField
    {
    private:
        EString     fComponentName;
    public:
        EComponentContainer(const EString& componentName);

        virtual const EString& GetDisplayName() const override;

        virtual bool OnRender() override;
    };


}