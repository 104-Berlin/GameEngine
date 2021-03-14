#pragma once

namespace Engine
{
    struct E_API EDragData
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


    struct E_API EUIClickEvent
    {
        u32 NOTHING = 0;
    };

    class E_API EUIField : public std::enable_shared_from_this<EUIField>
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
        virtual ~EUIField();

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

        template <typename Candidate>
        void SetOnClick(Candidate&& cb)
        {
            fEventDispatcher.Connect<EUIClickEvent>(cb);
        }

    };

    class E_API EUILabel : public EUIField
    {
    public:
        EUILabel(const EString& label);

        virtual bool OnRender() override;
    };

    class E_API EUIContainer : public EUIField
    {
    private:
        bool    fShow;
    public:
        EUIContainer(const EString& identifier = "EMPTY");

        virtual bool OnRender() override;

        void SetShow(bool value = true);
    };

    class E_API EUIPanel : public EUIField
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



    struct E_API EStringChangeEvent
    {
        EString Value;
    };
    #define STRING_BUFFER_SIZE 255
    class E_API EUIInputFieldString : public EUIField
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

    
    struct E_API EIntegerChangeEvent
    {
        i32 Value;
    };

    class E_API EUIInputFieldInteger : public EUIField
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


    struct E_API EFloatChangeEvent
    {
        float Value;
    };

    class E_API EUIInputFieldFloat : public EUIField
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

    struct E_API EFloat2ChangeEvent
    {
        EVec2 Value;
    };
    class E_API EUIInputFieldFloat2 : public EUIField
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

    struct E_API EFloat3ChangeEvent
    {
        EVec3 Value;
    };

    class E_API EUIInputFieldFloat3 : public EUIField
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

    struct E_API EFloat4ChangeEvent
    {
        EVec4 Value;
    };

    class E_API EUIInputFieldFloat4 : public EUIField
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

    struct E_API ECheckboxChangeEvent
    {
        bool Value;
    };
    class E_API EUICheckbox : public EUIField
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

    class E_API EUIMainMenuBar : public EUIField
    {
    private:
        bool fOpen;
    public:
        EUIMainMenuBar();

        virtual bool OnRender() override;
        virtual void OnRenderEnd() override;
        
    };

    class E_API EUIMenu : public EUIField
    {
    private:
        bool    fOpen;
    public:
        EUIMenu(const EString& displayName = "MenuBar");

        virtual bool OnRender() override;
        virtual void OnRenderEnd() override;
    };

    class E_API EUIContextMenu : public EUIField
    {
    private:
        bool        fOpen;
    public:
        EUIContextMenu(const EString& displayName = "ContextMenu");

        virtual bool OnRender() override;
        virtual void OnRenderEnd() override;
    };

    class E_API EUIMenuItem : public EUIField
    {
    public:
        EUIMenuItem(const EString& label);

        virtual bool OnRender() override;
    };

    class E_API EUISeperator : public EUIField
    {
    public:
        EUISeperator();

        virtual bool OnRender() override;
    };

    class E_API EUISelectable : public EUIField
    {
    public:
        EUISelectable(const EString& label);

        virtual bool OnRender() override;
    };


    class E_API EUIViewport : public EUIField
    {
        using RenderFunction = std::function<void(u32 screenWidth, u32 screenHeight)>;
    private:
        ERef<EFrameBuffer>  fFrameBuffer;
        RenderFunction      fRenderFunction;
        u32                 fViewportWidth;
        u32                 fViewportHeight;
    public:
        EUIViewport();

        void SetRenderFunc(RenderFunction function);

        virtual bool OnRender() override;
    };

    struct E_API EMeshChangeEvent
    {
        ERef<EMesh> Value;
    };

    class E_API EUIMeshInput : public EUIField
    {
    private:
        ERef<EFrameBuffer>  fFrameBuffer;
        ERef<EMesh>         fMesh;
    public:
        EUIMeshInput();

        void SetMesh(ERef<EMesh> mesh);

        virtual bool OnRender() override;

        template <typename T>
        void OnValueChange(T&& cb)
        {
            fEventDispatcher.Connect<EMeshChangeEvent>(cb);
        }
    };

    struct E_API ETextureChangeEvent
    {
        ERef<ETexture2D> Value;
    };

    class E_API EUITextureInput : public EUIField
    {
    private:
        ERef<ETexture2D>  fTexture;
    public:
        EUITextureInput();

        void SetTexture(ERef<ETexture2D> texture);

        virtual bool OnRender() override;

        template <typename T>
        void OnValueChange(T&& cb)
        {
            fEventDispatcher.Connect<ETextureChangeEvent>(cb);
        }
    };
}