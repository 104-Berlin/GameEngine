#pragma once

namespace Engine {
    class EUIField;
    namespace UI {
        E_API bool IsItemActiveLastFrame();
        E_API bool IsItemJustReleased();
        

        E_API ERef<EUIField> CreateInputField_Bool(const EString& label, EProperty<bool>* property);
        E_API ERef<EUIField> CreateInputField_Float(const EString& label, EProperty<float>* property);
        E_API ERef<EUIField> CreateInputField_Double(const EString& label, EProperty<double>* property);
        E_API ERef<EUIField> CreateInputField_I32(const EString& label, EProperty<i32>* property);
        E_API ERef<EUIField> CreateInputField_Vec3(const EString& label, EProperty<EVec3>* property);
        E_API ERef<EUIField> CreateInputField_Vec4(const EString& label, EProperty<EVec4>* property);
        E_API ERef<EUIField> CreateInputField_String(const EString& label, EProperty<EString>* property);
        E_API ERef<EUIField> CreateInputField_UUID(const EString& label, EProperty<EUUID>* property);
        E_API ERef<EUIField> CreateInputField_Mesh(const EString& label, EResourceProperty<EMesh>* property);
        E_API ERef<EUIField> CreateInputField_Texture(const EString& label, EResourceProperty<ETexture2D>* property);

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
        inline ERef<EUIField> CreateInputField<EResourceProperty<EMesh>*>(const EString& label, EResourceProperty<EMesh>* property) { return CreateInputField_Mesh(label, property); }
        template <>
        inline ERef<EUIField> CreateInputField<EResourceProperty<ETexture2D>*>(const EString& label, EResourceProperty<ETexture2D>* property) { return CreateInputField_Texture(label, property); }
        

        template <>
        inline ERef<EUIField> CreateInputField<EObjectProperty<ECamera>*>(const EString& label, EObjectProperty<ECamera>* value)
        {
            return nullptr;
        }
    }
}