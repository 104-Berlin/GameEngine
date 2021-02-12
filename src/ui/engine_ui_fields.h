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
        bool                            fIsDirty;
        EString                         fLabel;
    public:
        EUIField(const EString& label);

        EString GetDisplayName() const;

        void UpdateEvents();
        void Render();

        /**
         * @return wether or not the chidren should be rendered. Default is true
         * */
        virtual bool OnRender();
        virtual void OnRenderEnd();

        void SetUpdateFunction(UpdateFunction function);

        ERef<EUIField> AddChild(const ERef<EUIField>& child);
        void ClearChildren();

        void SetVisible(bool visible);
        void SetDirty(bool value = true);
        bool IsDirty() const;

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
    public:
        EUILabel(const EString& label);

        virtual bool OnRender() override;
    };

    class EUIContainer : public EUIField
    {
    public:
        EUIContainer(const EString& identifier = "EMPTY");

        virtual bool OnRender() override;
    };

    class EUIPanel : public EUIField
    {
    private:
        bool            fOpen;
        bool            fWasJustClosed; // This is used to remove a ImGui bug when we have to call ImGui::End once when we closed the panel
    public:
        EUIPanel(const EString& panelName);

        const EString& GetPanelTitle() const;

        virtual bool OnRender() override;
        virtual void OnRenderEnd() override;

        void Open();
        bool IsOpen() const;
    protected:
    };



    struct EStringChangeEvent
    {
        EString Value;
    };
    #define STRING_BUFFER_SIZE 255
    class EUIInputFieldString : public EUIField
    {
    private:
        char        fValue[STRING_BUFFER_SIZE];
    public:
        EUIInputFieldString(const EString& label);

        virtual bool OnRender() override;

        void SetValue(const EString& value);
        EString GetValue() const;

        template <typename T>
        void OnValueChange(T&& cb)
        {
            fEventDispatcher.Connect<EStringChangeEvent>(cb);
        }
    };

    
    struct EIntegerChangeEvent
    {
        i32 Value;
    };

    class EUIInputFieldInteger : public EUIField
    {
    private:
        i32     fValue;
    public:
        EUIInputFieldInteger(const EString& label);

        virtual bool OnRender() override;

        void SetValue(i32 value);
        i32 GetValue() const;

        template <typename T>
        void OnValueChange(T&& cb)
        {
            fEventDispatcher.Connect<EIntegerChangeEvent>(cb);
        }
    };


    struct EFloatChangeEvent
    {
        float Value;
    };

    class EUIInputFieldFloat : public EUIField
    {
    private:
        float   fValue;
    public:
        EUIInputFieldFloat(const EString& label);

        virtual bool OnRender() override;

        void SetValue(float value);
        float GetValue() const;

        template <typename T>
        void OnValueChange(T&& cb)
        {
            fEventDispatcher.Connect<EFloatChangeEvent>(cb);
        }
    };

    struct EFloat2ChangeEvent
    {
        EVec2 Value;
    };
    class EUIInputFieldFloat2 : public EUIField
    {
    private:
        EVec2   fValue;
    public:
        EUIInputFieldFloat2(const EString& label);

        virtual bool OnRender() override;

        void SetValue(const EVec2& value);
        EVec2 GetValue() const;

        template <typename T>
        void OnValueChange(T&& cb)
        {
            fEventDispatcher.Connect<EFloat2ChangeEvent>(cb);
        }
    };

    struct EFloat3ChangeEvent
    {
        EVec3 Value;
    };

    class EUIInputFieldFloat3 : public EUIField
    {
    private:
        EVec3   fValue;
    public:
        EUIInputFieldFloat3(const EString& label);

        virtual bool OnRender() override;

        void SetValue(const EVec3& value);
        EVec3 GetValue() const;

        template <typename T>
        void OnValueChange(T&& cb)
        {
            fEventDispatcher.Connect<EFloat3ChangeEvent>(cb);
        }
    };

    struct EFloat4ChangeEvent
    {
        EVec4 Value;
    };

    class EUIInputFieldFloat4 : public EUIField
    {
    private:
        EVec4   fValue;
    public:
        EUIInputFieldFloat4(const EString& label);

        virtual bool OnRender() override;

        void SetValue(const EVec4& value);
        EVec4 GetValue() const;

        template <typename T>
        void OnValueChange(T&& cb)
        {
            fEventDispatcher.Connect<EFloat4ChangeEvent>(cb);
        }
    };

    struct ECheckboxChangeEvent
    {
        bool Value;
    };
    class EUICheckbox : public EUIField
    {
    private:
        bool    fValue;
    public:
        EUICheckbox(const EString& label);

        virtual bool OnRender() override;

        void SetValue(bool value);
        bool GetValue() const;

        template <typename T>
        void OnValueChange(T&& cb)
        {
            fEventDispatcher.Connect<ECheckboxChangeEvent>(cb);
        }
    };

    class EUIComponentContainer : public EUIField
    {
    public:
        EUIComponentContainer(const EString& componentName);

        virtual bool OnRender() override;
        virtual void OnRenderEnd() override;
    };

    class EUIMainMenuBar : public EUIField
    {
    private:
        bool fOpen;
    public:
        EUIMainMenuBar();

        virtual bool OnRender() override;
        virtual void OnRenderEnd() override;
        
    };

    class EUIMenu : public EUIField
    {
    private:
        bool    fOpen;
    public:
        EUIMenu(const EString& displayName = "MenuBar");

        virtual bool OnRender() override;
        virtual void OnRenderEnd() override;
    };

    class EUIContextMenu : public EUIField
    {
    private:
        bool        fOpen;
    public:
        EUIContextMenu(const EString& displayName = "ContextMenu");

        virtual bool OnRender() override;
        virtual void OnRenderEnd() override;
    };

    class EUIMenuItem : public EUIField
    {
    public:
        EUIMenuItem(const EString& label);

        virtual bool OnRender() override;
    };



    class EUISelectable : public EUIField
    {
    public:
        EUISelectable(const EString& label);

        virtual bool OnRender() override;
    };

}