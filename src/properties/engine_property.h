#pragma once

namespace Engine {
    class EObject;

    typedef std::function<void()> EChangeFunc;

    class EBaseProperty
    {
    protected:
        EString                 fName;
        EUnorderedMap<intptr_t, EChangeFunc>    fBeforeChangeCallbacks;
        EUnorderedMap<intptr_t, EChangeFunc>    fAfterChangeCallbacks;
    public:
        EBaseProperty(const EString& name);

        void FromJsObject(const EJson& ref);
        void SetJsObject(EJson& ref) const;

        virtual void OnFromJsObject(const EJson& ref);
        virtual void OnSetJsObject(EJson& ref) const;
        
        const EString& GetPropertyName() const;
        void SetPropertyName(const EString& name);

        // Maybe return some kind of pointer in array to be able to remove it
        void AddEventBeforeChange(intptr_t key, const EChangeFunc& func);
        // void RemoveEventBeforeChange(EEventPosition p);
        void AddEventAfterChange(intptr_t key, const EChangeFunc& func);
        // void RemoveEventAfterChange(EEventPosition p);
    };

    class EObjectRef : public EBaseProperty
    {
    private:
        EObject*    fObject;
        EUUID       fObjectUuid;
    public:
        EObjectRef(const EString& propertyName);
        ~EObjectRef();

        void SetValue(const EObject& value);
        EObject& GetValue() const;

        virtual void OnFromJsObject(const EJson& ref) override;
        virtual void OnSetJsObject(EJson& ref) const override;
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

            for (const auto& f : fBeforeChangeCallbacks) {f.second();}

            *fValue = value;

            for (const auto& f : fAfterChangeCallbacks) {f.second();}
        }

        const Type& GetValue() const
        {
            return *fValue;
        }

        virtual void OnFromJsObject(const EJson& ref) override
        {
            if (JSHelper::HasParam(ref, GetPropertyName()))
            {
                Type newValue;
                JSHelper::ConvertObject(ref[GetPropertyName()], &newValue);
                SetValue(newValue);
            }
        }

        virtual void OnSetJsObject(EJson& ref) const override
        {
            ref[GetPropertyName()] = JSHelper::ConvertValue((const Type&) *fValue);
        }

        operator const Type&() const
        {
            return *fValue;
        }

        void operator =(const Type& other)
        {
            SetValue(other);
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

            for (const auto& f : fBeforeChangeCallbacks) {f.second();}

            fValue = value;

            for (const auto& f : fAfterChangeCallbacks) {f.second();}
        }
        
        void AddValue(const ListType& value)
        {
            for (const auto& f : fBeforeChangeCallbacks) {f.second();}

            fValue.push_back(value);

            for (const auto& f : fAfterChangeCallbacks) {f.second();}
        }

        void RemoveValue(const ListType& value)
        {
            #ifdef ENGINE_NO_NOT_IMPL
            std::cout << "EListProperty::RemoveValue NOT IMPLEMENTED! use #define ENGINE_NO_NOT_IMPL at the top of project to disable this call!" << std::endl;
            #endif
            /*EVector<ListType>::iterator it = std::find(fValue.begin(), fValue.end(), value);
            if (it != fValue.end())
            {
                for (const auto& f : fBeforeChangeCallbacks) {f.second();}

                fValue.erase(it);

                for (const auto& f : fAfterChangeCallbacks) {f.second();}
            }*/
        }

        void RemoveValue(size_t index)
        {
            if (index >= fValue.size()) { return; }

            for (const auto& f : fBeforeChangeCallbacks) {f.second();}
            fValue.erase(fValue.begin() + index);
            for (const auto& f : fAfterChangeCallbacks) {f.second();}
        }

        void ClearValue()
        {
            if (fValue.size() == 0) { return; }

            for (const auto& f : fBeforeChangeCallbacks) {f.second();}
            fValue.clear();
            for (const auto& f : fAfterChangeCallbacks) {f.second();}
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
        ERef<ObjectType>     fObjectValue;
    public:
        EObjectProperty(const EString& name, ERef<ObjectType> initValue = nullptr)
            : EBaseProperty(name)
        {
            fObjectValue = initValue;
        }

        void SetValue(ERef<ObjectType> object)
        {
            if (object == fObjectValue) { return; }

            for (auto func : fBeforeChangeCallbacks)
            {
                func.second();
            }

            fObjectValue = object;

            
            for (auto func : fAfterChangeCallbacks)
            {
                func.second();
            }
        }

        ERef<ObjectType> GetValue() const
        {
            return fObjectValue;
        }

        virtual void OnFromJsObject(const EJson& ref) override
        {
            if (JSHelper::HasParam(ref, GetPropertyName()))
            {
                //ObjectType** newValue = new ObjectType*;
                //JSHelper::ConvertObject(ref[GetPropertyName()], newValue);
                //SetValue(*newValue);
            }
        }

        virtual void OnSetJsObject(EJson& ref) const override
        {
            if (fObjectValue)
            {
                //fObjectValue->SetJsObject(ref[GetPropertyName()]);
            }
        }

        operator ERef<ObjectType>()
        {
            return fObjectValue;
        }

        ERef<ObjectType> operator ->()
        {
            return fObjectValue;
        }

        operator bool() const
        {
            return fObjectValue != nullptr;
        }

        void operator =(ERef<ObjectType> other)
        {
            SetValue(other);
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

            for (const auto& f : fBeforeChangeCallbacks) {f.second();}

            fValue = value;

            for (const auto& f : fAfterChangeCallbacks) {f.second();}
        }
        
        void AddValue(ObjectType* value)
        {
            for (const auto& f : fBeforeChangeCallbacks) {f.second();}

            fValue.push_back(value);

            for (const auto& f : fAfterChangeCallbacks) {f.second();}
        }

        void RemoveValue(ObjectType* value)
        {
            fValue.erase(value);
        }

        void RemoveValue(size_t index)
        {
            if (index >= fValue.size()) { return; }

            for (const auto& f : fBeforeChangeCallbacks) {f.second();}
            fValue.erase(fValue.begin() + index);
            for (const auto& f : fAfterChangeCallbacks) {f.second();}
        }

        void ClearValue()
        {
            if (fValue.size() == 0) { return; }

            for (const auto& f : fBeforeChangeCallbacks) {f.second();}
            fValue.clear();
            for (const auto& f : fAfterChangeCallbacks) {f.second();}
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