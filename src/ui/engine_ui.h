#pragma once

namespace Engine {

    namespace UI {

        void Init(EWindow& window);
        void NewFrame();
        void Render();




        // Component panel ui

        struct InputFieldIter
        {
            template <class Obj>
            void convert(Obj* obj)
            {
                obj->_reflect(*this);
            }

            template <class Obj, class Field>
            void operator()(Obj* obj, const char* name, Field& field);
        };

        void RenderInputField(const EString& label, bool* value);
        void RenderInputField(const EString& label, float* value);
        void RenderInputField(const EString& label, double* value);
        void RenderInputField(const EString& label, i32* value);
        void RenderInputField(const EString& label, EVec3* value);
        void RenderInputField(const EString& label, EVec4* value);
        void RenderInputField(const EString& label, EString* value);

        template <typename T>
        auto RenderInputField(const EString& label, T* object)
        -> decltype(T::_reflect_arg_count, void())
        {
            InputFieldIter iter;
            iter.convert(object);
        }

        template <class Obj, class Field>
        void InputFieldIter::operator() (Obj* obj, const char* name, Field& field)
        {
            RenderInputField(name, &field);
        }


        void RenderComponentPanel(EObject object);

    }

}