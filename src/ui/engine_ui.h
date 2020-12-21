#pragma once

namespace Engine {

    namespace UI {

        bool IsItemActiveLastFrame();

        static bool IsItemJustReleased()
        {
            return IsItemActiveLastFrame() && !ImGui::IsItemActive();
        }



        void Init(EWindow& window);
        void NewFrame();
        void Render();




        // Component panel ui

        struct InputFieldIter
        {
        private:
            EString fLabel;
        public:
            InputFieldIter(const EString& label) : fLabel(label) {}

            template <class Obj>
            void convert(Obj* obj)
            {
                obj->_reflect(*this);
            }

            template <class Obj, class Field>
            void operator()(Obj* obj, const char* name, Field& field);
        };


        static void RenderInputField(const EString& label, EProperty<bool>& value) 
        {
            bool val = value.GetValue();
            if (ImGui::Checkbox(label.c_str(), &val))
            {
                value.SetValue(val);
            }
        }

        static void RenderInputField(const EString& label, EProperty<float>& value) 
        {
            float val = value.GetValue();
            if (ImGui::DragFloat(label.c_str(), &val))
            {
                value.SetValue(val);
            }
        }

        static void RenderInputField(const EString& label, EProperty<double>& value) 
        {
            double val = value.GetValue();
            if (ImGui::InputDouble(label.c_str(), &val, 0.0f, 0.0f, "%.6f", ImGuiInputTextFlags_EnterReturnsTrue))
            {   
                value.SetValue(val);
                std::cout << "Doulbe changed" << std::endl;
            }
        }

        static void RenderInputField(const EString& label, EProperty<i32>& value) 
        {
            i32 val = value.GetValue();
            if (ImGui::DragInt(label.c_str(), &val))
            {
                value.SetValue(val);
            }
        }

        static void RenderInputField(const EString& label, EProperty<EVec3>& value) 
        {
            EVec3 val = value.GetValue();
            if (ImGui::DragFloat3(label.c_str(), &val.x))
            {
                value.SetValue(val);
            }
        }

        static void RenderInputField(const EString& label, EProperty<EVec4>& value) 
        {
            EVec4 val = value.GetValue();
            if (ImGui::DragFloat4(label.c_str(), &val.x))
            {
                value.SetValue(val);
            }
        }

        static void RenderInputField(const EString& label, EProperty<EString>& value) 
        {
            size_t bufferSize = 256 * sizeof(char);
            char* buffer = (char*) malloc(bufferSize);
            memset(buffer, 0, bufferSize);
            strcpy(buffer, value.GetValue().c_str());
            if (ImGui::InputText(label.c_str(), buffer, bufferSize, ImGuiInputTextFlags_EnterReturnsTrue))
            {
                value.SetValue(buffer);
                std::cout << "String changed" << std::endl;
            }
        }

        static void RenderInputField(const EString& label, EProperty<EUUID>& value) 
        {
            ImGui::Text("%s", label.c_str());
            ImGui::SameLine();
            ImGui::Text("%s", value.GetValue().ToString().c_str());
        }

        template <typename T>
        auto RenderInputField(const EString& label, T* object)
        -> decltype(T::_reflect_arg_count, void())
        {
            InputFieldIter iter(label);
            if (ImGui::CollapsingHeader(label.c_str()))
            {
                iter.convert(object);
            }
        }

        template <class Obj, class Field>
        void InputFieldIter::operator() (Obj* obj, const char* name, Field& field)
        {
            RenderInputField(name, field);
        }


        void RenderComponentPanel(EObject object);

    }

}