#pragma once

namespace Engine {
    namespace UI {
    bool IsItemActiveLastFrame();

    static bool IsItemJustReleased()
    {
        return IsItemActiveLastFrame() && !ImGui::IsItemActive();
    }


    template <typename T>
    inline void RenderInputField(const EString& label, T value);


    template <>
    inline void RenderInputField<EProperty<bool>*>(const EString& label, EProperty<bool>* value)
    {
        bool val = value->GetValue();
        if (ImGui::Checkbox(label.c_str(), &val))
        {
            value->SetValue(val);
        }
    }

    template <>
    inline void RenderInputField<EProperty<float>*>(const EString& label, EProperty<float>* value)
    {
        double val = value->GetValue();
        if (ImGui::InputDouble(label.c_str(), &val, 0.0f, 0.0f, "%.6f", ImGuiInputTextFlags_EnterReturnsTrue))
        {   
            value->SetValue(val);
            std::cout << "Doulbe changed" << std::endl;
        }
    }

    template <>
    inline void RenderInputField<EProperty<double>*>(const EString& label, EProperty<double>* value)
    {
        float val = value->GetValue();
        if (ImGui::DragFloat(label.c_str(), &val))
        {
            value->SetValue(val);
        }
    }

    template <>
    inline void RenderInputField<EProperty<i32>*>(const EString& label, EProperty<i32>* value)
    {
        i32 val = value->GetValue();
        if (ImGui::DragInt(label.c_str(), &val))
        {
            value->SetValue(val);
        }
    }

    template <>
    inline void RenderInputField<EProperty<EVec3>*>(const EString& label, EProperty<EVec3>* value)
    {
        EVec3 val = value->GetValue();
        if (ImGui::DragFloat3(label.c_str(), &val.x, 0.1f, -10000.0f, 10000.0f, "%.3f"))
        {
            value->SetValue(val);
        }
    }
    
    template <>
    inline void RenderInputField<EProperty<EVec4>*>(const EString& label, EProperty<EVec4>* value)
    {
        EVec4 val = value->GetValue();
        if (ImGui::DragFloat4(label.c_str(), &val.x, 0.1f, -10000.0f, 10000.0f, "%.3f"))
        {
            value->SetValue(val);
        }
    }

    template <>
    inline void RenderInputField<EProperty<EString>*>(const EString& label, EProperty<EString>* value)
    {
        size_t bufferSize = 256 * sizeof(char);
        char* buffer = (char*) malloc(bufferSize);
        memset(buffer, 0, bufferSize);
        strcpy(buffer, value->GetValue().c_str());
        if (ImGui::InputText(label.c_str(), buffer, bufferSize, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            value->SetValue(buffer);
            std::cout << "String changed" << std::endl;
        }
    }

    template <>
    inline void RenderInputField<EProperty<EUUID>*>(const EString& label, EProperty<EUUID>* value)
    {
        ImGui::Text("%s", label.c_str());
        ImGui::SameLine();
        ImGui::Text("%s", value->GetValue().ToString().c_str());
    }
    }
}