#pragma once

namespace Engine {
    class EUIField;
    namespace UI {
        bool IsItemActiveLastFrame();
        bool IsItemJustReleased();
        

        ERef<EUIField> CreateInputField_Bool(const EString& label, EProperty<bool>* property);
        ERef<EUIField> CreateInputField_Float(const EString& label, EProperty<float>* property);
        ERef<EUIField> CreateInputField_Double(const EString& label, EProperty<double>* property);
        ERef<EUIField> CreateInputField_I32(const EString& label, EProperty<i32>* property);
        ERef<EUIField> CreateInputField_Vec3(const EString& label, EProperty<EVec3>* property);
        ERef<EUIField> CreateInputField_Vec4(const EString& label, EProperty<EVec4>* property);
        ERef<EUIField> CreateInputField_String(const EString& label, EProperty<EString>* property);
        ERef<EUIField> CreateInputField_UUID(const EString& label, EProperty<EUUID>* property);
        ERef<EUIField> CreateInputField_Mesh(const EString& label, EObjectProperty<EMesh>* property);

        template <typename T>
        inline ERef<EUIField> CreateInputField(const EString& label, T property);

        template <>
        inline ERef<EUIField> CreateInputField<EProperty<bool>*>(const EString& label, EProperty<bool>* property) { return CreateInputField_Bool(label, property); }
        template <>
        inline ERef<EUIField> CreateInputField<EProperty<float>*>(const EString& label, EProperty<float>* property) { return CreateInputField_Float(label, property); }
        template <>
        inline ERef<EUIField> CreateInputField<EProperty<double>*>(const EString& label, EProperty<double>* property) { return CreateInputField_Double(label, property); }
        template <>
        inline ERef<EUIField> CreateInputField<EProperty<i32>*>(const EString& label, EProperty<i32>* property) { return CreateInputField_I32(label, property); }
        template <>
        inline ERef<EUIField> CreateInputField<EProperty<EVec3>*>(const EString& label, EProperty<EVec3>* property) { return CreateInputField_Vec3(label, property); }
        template <>
        inline ERef<EUIField> CreateInputField<EProperty<EVec4>*>(const EString& label, EProperty<EVec4>* property) { return CreateInputField_Vec4(label, property); }
        template <>
        inline ERef<EUIField> CreateInputField<EProperty<EString>*>(const EString& label, EProperty<EString>* property) { return CreateInputField_String(label, property); }
        template <>
        inline ERef<EUIField> CreateInputField<EProperty<EUUID>*>(const EString& label, EProperty<EUUID>* property) { return CreateInputField_UUID(label, property); }
        template <>
        inline ERef<EUIField> CreateInputField<EObjectProperty<EMesh>*>(const EString& label, EObjectProperty<EMesh>* property) { return CreateInputField_Mesh(label, property); }

        template <>
        inline ERef<EUIField> CreateInputField<EObjectProperty<ETexture2D>*>(const EString& label, EObjectProperty<ETexture2D>* value)
        {
            return nullptr;
        }


        template <>
        inline ERef<EUIField> CreateInputField<EObjectProperty<ECamera>*>(const EString& label, EObjectProperty<ECamera>* value)
        {
            return nullptr;
        }
    }
}