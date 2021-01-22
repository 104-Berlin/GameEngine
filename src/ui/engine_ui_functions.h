#pragma once

namespace Engine {
    namespace UI {
    bool IsItemActiveLastFrame();

    static bool IsItemJustReleased()
    {
        return IsItemActiveLastFrame() && !ImGui::IsItemActive();
    }


    void RenderInputField_Bool(const EString& label, EProperty<bool>* value);
    void RenderInputField_Float(const EString& label, EProperty<float>* value);
    void RenderInputField_Double(const EString& label, EProperty<double>* value);
    void RenderInputField_I32(const EString& label, EProperty<i32>* value);
    void RenderInputField_Vec3(const EString& label, EProperty<EVec3>* value);
    void RenderInputField_Vec4(const EString& label, EProperty<EVec4>* value);
    void RenderInputField_String(const EString& label, EProperty<EString>* value);
    void RenderInputField_UUID(const EString& label, EProperty<EUUID>* value);

    template <typename T>
    inline void RenderInputField(const EString& label, T value);


    template <>
    inline void RenderInputField<EProperty<bool>*>(const EString& label, EProperty<bool>* value)
    {
        RenderInputField_Bool(label, value);
    }

    template <>
    inline void RenderInputField<EProperty<float>*>(const EString& label, EProperty<float>* value)
    {
        RenderInputField_Float(label, value);
    }

    template <>
    inline void RenderInputField<EProperty<double>*>(const EString& label, EProperty<double>* value)
    {
        RenderInputField_Double(label, value);
    }

    template <>
    inline void RenderInputField<EProperty<i32>*>(const EString& label, EProperty<i32>* value)
    {
        RenderInputField_I32(label, value);
    }

    template <>
    inline void RenderInputField<EProperty<EVec3>*>(const EString& label, EProperty<EVec3>* value)
    {
        RenderInputField_Vec3(label, value);
    }
    
    template <>
    inline void RenderInputField<EProperty<EVec4>*>(const EString& label, EProperty<EVec4>* value)
    {
        RenderInputField_Vec4(label, value);
    }

    template <>
    inline void RenderInputField<EProperty<EString>*>(const EString& label, EProperty<EString>* value)
    {
        RenderInputField_String(label, value);
    }

    template <>
    inline void RenderInputField<EProperty<EUUID>*>(const EString& label, EProperty<EUUID>* value)
    {
        RenderInputField_UUID(label, value);
    }
    }
}