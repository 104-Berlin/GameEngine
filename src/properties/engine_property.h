#pragma once

namespace Engine {

    typedef std::function<void()> EChangeFunc;

    class EBaseProperty
    {
    protected:
        EString                 fName;
        EVector<EChangeFunc>    fBeforeChangeCallbacks;
        EVector<EChangeFunc>    fAfterChangeCallbacks;
    public:
        EBaseProperty(const EString& name);

        void FromJsObject(const EJson& ref);
        void SetJsObject(EJson& ref) const;

        virtual void OnFromJsObject(const EJson& ref);
        virtual void OnSetJsObject(EJson& ref) const;
        
        const EString& GetPropertyName() const;
        void SetPropertyName(const EString& name);

        // Maybe return some kind of pointer in array to be able to remove it
        void AddEventBeforeChange(const EChangeFunc& func);
        // void RemoveEventBeforeChange(EEventPosition p);
        void AddEventAfterChange(const EChangeFunc& func);
        // void RemoveEventAfterChange(EEventPosition p);
    };

    template <typename Type>
    class EProperty : public EBaseProperty
    {
    private:
        ERef<Type> fValue;
    public:
        EProperty(const EString& name, const Type& value = Type())
            : EBaseProperty(name)
        {
            fValue = EMakeRef(Type);
            *fValue = value;
        }

        EProperty(const EProperty& other) = default;

        ~EProperty()
        {}

        void SetValue(const Type& value)
        {
            if (value == *fValue) { return; }

            for (const EChangeFunc& f : fBeforeChangeCallbacks) {f();}

            *fValue = value;

            for (const EChangeFunc& f : fAfterChangeCallbacks) {f();}
        }

        const Type& GetValue() const
        {
            return *fValue;
        }

        virtual void OnFromJsObject(const EJson& ref) override
        {
            if (JSHelper::HasParam(ref, fName))
            {
                JSHelper::ConvertObject(ref, fValue.get());
            }
        }

        virtual void OnSetJsObject(EJson& ref) const override
        {
            ref[fName] = JSHelper::ConvertValue((const Type&) *fValue);
        }
    };

    template <typename ListType>
    class EListProperty : public EBaseProperty
    {
    private:
        EVector<ListType> fValue;
    public:
        EListProperty(const EString& name)
            : EBaseProperty(name)
        {

        }

        void SetValue(const EVector<ListType>& value)
        {
            if (fValue == value) { return; }

            for (const EChangeFunc& f : fBeforeChangeCallbacks) {f();}

            fValue = value;

            for (const EChangeFunc& f : fAfterChangeCallbacks) {f();}
        }
        
        void AddValue(const ListType& value)
        {
            for (const EChangeFunc& f : fBeforeChangeCallbacks) {f();}

            fValue.push_back(value);

            for (const EChangeFunc& f : fAfterChangeCallbacks) {f();}
        }

        void RemoveValue(const ListType& value)
        {
            #ifdef ENGINE_NO_NOT_IMPL
            std::cout << "EListProperty::RemoveValue NOT IMPLEMENTED! use #define ENGINE_NO_NOT_IMPL at the top of project to disable this call!" << std::endl;
            #endif
            /*EVector<ListType>::iterator it = std::find(fValue.begin(), fValue.end(), value);
            if (it != fValue.end())
            {
                for (const EChangeFunc& f : fBeforeChangeCallbacks) {f();}

                fValue.erase(it);

                for (const EChangeFunc& f : fAfterChangeCallbacks) {f();}
            }*/
        }

        void RemoveValue(size_t index)
        {
            if (index >= fValue.size()) { return; }

            for (const EChangeFunc& f : fBeforeChangeCallbacks) {f();}
            fValue.erase(fValue.begin() + index);
            for (const EChangeFunc& f : fAfterChangeCallbacks) {f();}
        }

        void ClearValue()
        {
            if (fValue.size() == 0) { return; }

            for (const EChangeFunc& f : fBeforeChangeCallbacks) {f();}
            fValue.clear();
            for (const EChangeFunc& f : fAfterChangeCallbacks) {f();}
        }

        virtual void OnFromJsObject(const EJson& ref) override
        {
            if (JSHelper::HasParam(ref, fName) && ref[fName].is_array())
            {
                JSHelper::ConvertObject(ref[fName], &fValue);
            }
        }

        virtual void OnSetJsObject(EJson& ref) const override
        {
            ref[fName] = JSHelper::ConvertValue(fValue);
        }
    };

    template <typename ObjectType>
    class EObjectProperty : public EBaseProperty
    {
    private:
        ObjectType*     fObjectValue;
    public:
        EObjectProperty(const EString& name)
            : EBaseProperty(name)
        {
            fObjectValue = nullptr;
        }

        void SetValue(ObjectType* object)
        {
            if (object == fObjectValue) { return; }

            for (auto func : fBeforeChangeCallbacks)
            {
                func();
            }

            fObjectValue = object;

            
            for (auto func : fAfterChangeCallbacks)
            {
                func();
            }
        }

        ObjectType* GetValue() const
        {
            return fObjectValue;
        }

        virtual void OnFromJsObject(const EJson& ref) override
        {
            if (JSHelper::HasParam(ref, GetPropertyName()))
            {
                ObjectType** newValue = new ObjectType*;
                JSHelper::ConvertObject(ref[GetPropertyName()], newValue);
                SetValue(*newValue);
            }
        }

        virtual void OnSetJsObject(EJson& ref) const override
        {
            if (fObjectValue)
            {
                fObjectValue->SetJsObject(ref[GetPropertyName()]);
            }
        }
    };

    template <typename ObjectType>
    class EObjectListProperty : public EBaseProperty
    {
    private:
        EVector<ObjectType*> fValue;
    public:
        EObjectListProperty(const EString& name)
            : EBaseProperty(name)
        {

        }

        void SetValue(const EVector<ObjectType*>& value)
        {
            if (fValue == value) { return; }

            for (const EChangeFunc& f : fBeforeChangeCallbacks) {f();}

            fValue = value;

            for (const EChangeFunc& f : fAfterChangeCallbacks) {f();}
        }
        
        void AddValue(ObjectType* value)
        {
            for (const EChangeFunc& f : fBeforeChangeCallbacks) {f();}

            fValue.push_back(value);

            for (const EChangeFunc& f : fAfterChangeCallbacks) {f();}
        }

        void RemoveValue(ObjectType* value)
        {
            fValue.erase(value);
        }

        void RemoveValue(size_t index)
        {
            if (index >= fValue.size()) { return; }

            for (const EChangeFunc& f : fBeforeChangeCallbacks) {f();}
            fValue.erase(fValue.begin() + index);
            for (const EChangeFunc& f : fAfterChangeCallbacks) {f();}
        }

        void ClearValue()
        {
            if (fValue.size() == 0) { return; }

            for (const EChangeFunc& f : fBeforeChangeCallbacks) {f();}
            fValue.clear();
            for (const EChangeFunc& f : fAfterChangeCallbacks) {f();}
        }

        virtual void OnFromJsObject(const EJson& ref) override
        {
            if (JSHelper::HasParam(ref, fName) && ref[fName].is_array())
            {
                JSHelper::ConvertObject(ref[fName], &fValue);
            }
        }

        virtual void OnSetJsObject(EJson& ref) const override
        {
            ref[fName] = JSHelper::ConvertValue(fValue);
        }
    };

}