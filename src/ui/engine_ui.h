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


        void RenderInputField(const EString& label, EBaseProperty* value);
        void RenderInputField(const EString& label, EProperty<bool>* value);
        void RenderInputField(const EString& label, EProperty<float>* value);
        void RenderInputField(const EString& label, EProperty<double>* value);
        void RenderInputField(const EString& label, EProperty<i32>* value);
        void RenderInputField(const EString& label, EProperty<EVec3>* value);
        void RenderInputField(const EString& label, EProperty<EVec4>* value);
        void RenderInputField(const EString& label, EProperty<EString>* value);
        void RenderInputField(const EString& label, EProperty<EUUID>* value);
        void RenderInputField(const EString& label, EObjectProperty<ETexture2D>* value);
        void RenderInputField(const EString& label, EObjectProperty<EMesh>* value);
        void RenderInputField(const EString& label, EObjectProperty<ECamera>* value);

        template <typename T>
        auto RenderInputField(const EString& label, T* object)
        -> decltype(T::_reflect_arg_count, void())
        {
            if (ImGui::CollapsingHeader(label.c_str()))
            {
                object->_reflect([](const char* name, auto* field){
                    RenderInputField(name, field);
                });
            }
        }

        template <class Obj, class Field>
        void InputFieldIter::operator() (Obj* obj, const char* name, Field& field)
        {
            RenderInputField(name, field);
        }


        void RenderComponentPanel(EObject object);




        // Resource manager

        void RenderResourcePanel(EResourceManager& resourceManager);

    }


}