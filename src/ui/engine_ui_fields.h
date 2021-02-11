#pragma once

namespace Engine
{
    struct EDragData
    {
        EString Type;
        void*   Buffer;
        size_t  Size;
    };

    static i32 next_ui_id()
    {
        static i32 currentUiId = 0;
        return ++currentUiId; 
    }

    typedef std::function<void()> EUICallbackFn;


    struct EUIClickEvent
    {
        u32 NOTHING = 0;
    };

    class EUIField : public std::enable_shared_from_this<EUIField>
    {
        using UpdateFunction = std::function<void(ERef<EUIField>)>;
        using DropFunction = std::function<void(EDragData)>;
    protected:
        EVector<ERef<EUIField>>         fChildren;
        i32                             fId;
        EUICallbackFn                   fOnClickCallback;
        bool                            fVisible;
        UpdateFunction                  fCustomUpdateFunction;
        EDragData                       fDragData;
        std::pair<EString, DropFunction>fDropFunction;
        EEventDispatcher                fEventDispatcher;
    public:
        EUIField();

        virtual const EString& GetDisplayName() const = 0;

        void Update();
        void UpdateEvents();
        void Render();

        /**
         * @return wether or not the chidren should be rendered. Default is true
         * */
        virtual bool OnRender();
        virtual void OnRenderEnd();

        virtual void OnUpdate();
        void SetUpdateFunction(UpdateFunction function);

        ERef<EUIField> AddChild(const ERef<EUIField>& child);
        void ClearChildren();

        void SetVisible(bool visible);


        // Drag and drop
        void SetDragData(EDragData data);

        void OnDrop(const EString& type, DropFunction dropFunction);

        // Add event listeners
        EEventDispatcher& GetEventDispatcher();

        /*template <typename Candidate>
        void SetOnClick()
        {
            fEventDispatcher.sink<EUIClickEvent>().connect<Candidate>();
        }*/



        /*template <typename Condidate, typename Type>
        void SetOnClick(Type&& args)
        {
            fEventDispatcher.sink<EUIClickEvent>().connect<Condidate>(args);
        }*/


    };

    class EUILabel : public EUIField
    {
    private:
        EString fLabel;
    public:
        EUILabel(const EString& label);

        virtual const EString& GetDisplayName() const override;

        virtual bool OnRender() override;
    };

    class EUIContainer : public EUIField
    {
    private:
        EString     fStringId;
    public:
        EUIContainer(const EString& identifier = "EMPTY");

        virtual const EString& GetDisplayName() const override;

        virtual bool OnRender() override;
    };

    class EUIPanel : public EUIField
    {
    private:
        EString         fName;
        bool            fOpen;
        bool            fWasJustClosed; // This is used to remove a ImGui bug when we have to call ImGui::End once when we closed the panel
    public:
        EUIPanel(const EString& panelName);

        virtual const EString& GetDisplayName() const override;

        virtual bool OnRender() override;
        virtual void OnRenderEnd() override;

        void Open();
        bool IsOpen() const;
    protected:
    };


    template <typename Renderable>
    class EInputField : public EUIField
    {
    private:
        Renderable fProperty;
    public:
        EInputField(Renderable property)
            : fProperty(property)
        {

        }

        virtual const EString& GetDisplayName() const override
        {
            return fProperty->GetPropertyName();
        }

        virtual bool OnRender() override
        {
            UI::RenderInputField(fProperty->GetPropertyName(), fProperty);
            return true; // ?
        }
    };

    class EComponentContainer : public EUIField
    {
    private:
        EString     fComponentName;
    public:
        EComponentContainer(const EString& componentName);

        virtual const EString& GetDisplayName() const override;

        virtual bool OnRender() override;
        virtual void OnRenderEnd() override;
    };

    class EMainMenuBar : public EUIField
    {
    private:
        bool fOpen;
    public:
        EMainMenuBar();

        virtual const EString& GetDisplayName() const override;

        virtual bool OnRender() override;
        virtual void OnRenderEnd() override;
        
    };

    class EUIMenu : public EUIField
    {
    private:
        EString fDisplayName;
        bool    fOpen;
    public:
        EUIMenu(const EString& displayName = "MenuBar");


        virtual const EString& GetDisplayName() const override;

        virtual bool OnRender() override;
        virtual void OnRenderEnd() override;
    };

    class EUIContextMenu : public EUIField
    {
    private:
        EString     fDisplayName;
        bool        fOpen;
    public:
        EUIContextMenu(const EString& displayName = "ContextMenu");

        virtual const EString& GetDisplayName() const override;

        virtual bool OnRender() override;
        virtual void OnRenderEnd() override;
    };

    class EUIMenuItem : public EUIField
    {
    private:
        EString fLabel;
    public:
        EUIMenuItem(const EString& label);

        virtual const EString& GetDisplayName() const override;

        virtual bool OnRender() override;
    };



    class EUISelectable : public EUIField
    {
    private:
        EString fLabel;
    public:
        EUISelectable(const EString& label);

        virtual const EString& GetDisplayName() const override;

        virtual bool OnRender() override;
    };

}