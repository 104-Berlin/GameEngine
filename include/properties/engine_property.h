#pragma once

namespace Engine {

    typedef std::function<void()> EChangeFunc;

    class EBaseProperty
    {
    protected:
        EString                 fName;
        EObject*                fObject;
        EVector<EChangeFunc>    fBeforeChangeCallbacks;
        EVector<EChangeFunc>    fAfterChangeCallbacks;
    public:
        EBaseProperty(EObject* object, const EString& name);

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
        Type* fValue;
    public:
        EProperty(EObject* object, const EString& name)
            : EBaseProperty(object, name)
        {
            fValue = new Type();
        }

        EProperty(const EProperty& other)
            : EProperty(other.fObject, other.fName)
        {
            *fValue = *other.fValue;
        }

        ~EProperty()
        {
            delete fValue;
        }

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
                JSHelper::ConvertObject(ref, fValue);
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
        EListProperty(EObject* object, const EString& name)
            : EBaseProperty(object, name)
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