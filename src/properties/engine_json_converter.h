#pragma once

#define EMPTY 
#define REM(...) __VA_ARGS__
#define EAT(...)

#define EXPAND( x ) x

// Strip off the type
#define STRIP(x) EAT x
// Show the type without parenthesis
#define PAIR(x) REM x

#define CONCATENATE(arg1, arg2)   CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2)  CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2)  arg1##arg2


#define ARG_COUNT(...) EXPAND(PP_SIZE(__VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,))
#define PP_SIZE(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, e62, e63, size, ...) size


#define STRINGIFY_FIELD(x) STRINGIFY_FIELD_A(x)
#define STRINGIFY_FIELD_A(x) STRINGIFY_FIELD_B(x)
#define STRINGIFY_FIELD_B(x) #x

#define LR_GET_FIELD(type, name) type name
#define LR_GET_PROP_NAME(type, name) name

#define LR_FIELD(field) EXPAND(LR_GET_FIELD field );
#define LR_SINGLE_REFLECT_METHOD(field) v ( this, STRINGIFY_FIELD(EXPAND(LR_GET_PROP_NAME field)), LR_GET_PROP_NAME field);



#define LR_RUN_1(FUNCTION, arg, ...) EXPAND(FUNCTION (arg))
#define LR_RUN_2(FUNCTION, arg, ...) EXPAND(FUNCTION (arg))\
                                EXPAND(LR_RUN_1 (FUNCTION, __VA_ARGS__))
#define LR_RUN_3(FUNCTION, arg, ...) EXPAND(FUNCTION (arg))\
                                EXPAND(LR_RUN_2 (FUNCTION, __VA_ARGS__))
#define LR_RUN_4(FUNCTION, arg, ...) EXPAND(FUNCTION (arg))\
                                EXPAND(LR_RUN_3 (FUNCTION, __VA_ARGS__))
#define LR_RUN_5(FUNCTION, arg, ...) EXPAND(FUNCTION (arg))\
                                EXPAND(LR_RUN_4 (FUNCTION, __VA_ARGS__))
#define LR_RUN_6(FUNCTION, arg, ...) EXPAND(FUNCTION (arg))\
                                EXPAND(LR_RUN_5 (FUNCTION, __VA_ARGS__))
#define LR_RUN_7(FUNCTION, arg, ...) EXPAND(FUNCTION (arg))\
                                EXPAND(LR_RUN_6 (FUNCTION, __VA_ARGS__))
#define LR_RUN_8(FUNCTION, arg, ...) EXPAND(FUNCTION (arg))\
                                EXPAND(LR_RUN_7 (FUNCTION, __VA_ARGS__))
#define LR_RUN_9(FUNCTION, arg, ...) EXPAND(FUNCTION (arg))\
                                EXPAND(LR_RUN_8 (FUNCTION, __VA_ARGS__))
#define LR_RUN_10(FUNCTION, arg, ...) EXPAND(FUNCTION (arg))\
                                EXPAND(LR_RUN_9 (FUNCTION, __VA_ARGS__))
#define LR_RUN_11(FUNCTION, arg, ...) EXPAND(FUNCTION (arg))\
                                EXPAND(LR_RUN_10 (FUNCTION, __VA_ARGS__))
#define LR_RUN_12(FUNCTION, arg, ...) EXPAND(FUNCTION (arg))\
                                EXPAND(LR_RUN_11 (FUNCTION, __VA_ARGS__))
#define LR_RUN_13(FUNCTION, arg, ...) EXPAND(FUNCTION (arg))\
                                EXPAND(LR_RUN_12 (FUNCTION, __VA_ARGS__))
#define LR_RUN_14(FUNCTION, arg, ...) EXPAND(FUNCTION (arg))\
                                EXPAND(LR_RUN_13 (FUNCTION, __VA_ARGS__))
#define LR_RUN_15(FUNCTION, arg, ...) EXPAND(FUNCTION (arg))\
                                EXPAND(LR_RUN_14 (FUNCTION, __VA_ARGS__))
#define LR_RUN_16(FUNCTION, arg, ...) EXPAND(FUNCTION (arg))\
                                EXPAND(LR_RUN_15 (FUNCTION, __VA_ARGS__))
#define LR_RUN_17(FUNCTION, arg, ...) EXPAND(FUNCTION (arg))\
                                EXPAND(LR_RUN_16 (FUNCTION, __VA_ARGS__))



#define LR_RUN_N(FUNCTION, N, ...) EXPAND(CONCATENATE(LR_RUN_, N) (FUNCTION, __VA_ARGS__))



#define REFLECT_METHOD(t, N, ...) \
                    template <class Visitor>\
                    void _reflect(Visitor& v) t {\
                        EXPAND(LR_RUN_N(LR_SINGLE_REFLECT_METHOD, N, __VA_ARGS__))\
                    }


#define REFLACTABLE(...)    static const int _reflect_arg_count = ARG_COUNT(__VA_ARGS__);\
                            EXPAND(LR_RUN_N(LR_FIELD, EXPAND(ARG_COUNT(__VA_ARGS__)), __VA_ARGS__))\
                            EXPAND(REFLECT_METHOD(EMPTY, EXPAND(ARG_COUNT(__VA_ARGS__)), __VA_ARGS__))\
                            EXPAND(REFLECT_METHOD(const, EXPAND(ARG_COUNT(__VA_ARGS__)), __VA_ARGS__))


namespace Engine {

    namespace JSHelper {

        bool HasParam(const EJson& ref, const EString& param);



        struct StructJsonConverter
        {
        private:
            EJson& fRef;
        public:
            StructJsonConverter(EJson& _ref) :fRef(_ref) {}

            template <class Obj>
            void convert(const Obj& obj) {
                obj._reflect(*this);
            }

            template <class Obj>
            void convert(Obj* obj) {
                obj->_reflect(*this);
            }

            template <class Obj, class Field>
            void operator() (const Obj* obj, const char* name, const Field& field);
        };
    
        class JsonStructConverter
        {
        private:
            const EJson& fRef;
        public:
            JsonStructConverter(const EJson& ref) : fRef(ref) {}

            template <class Obj>
            void convert(Obj& obj)
            {
                obj._reflect(*this);
            }

            template <class Obj>
            void convert(Obj* obj)
            {
                obj->_reflect(*this);
            }

            template <class Obj, class Field>
            void operator() (Obj* obj, const char* name, Field& field);
        };

        EJson ConvertValue(const bool value);
        EJson ConvertValue(const i32 value);
        EJson ConvertValue(const float value);
        EJson ConvertValue(const double value);
        EJson ConvertValue(const EString& value);
        EJson ConvertValue(const EUUID& value);
        EJson ConvertValue(const EVec2& value);
        EJson ConvertValue(const EVec3& value);
        EJson ConvertValue(const EVec4& value);

        EJson ConvertValue(EObject* object);

        template <typename T>
        auto ConvertValue(const T& value)
        -> decltype(T::_reflect_arg_count, EJson::object())
        {
            EJson result = EJson::object();
            StructJsonConverter converter(result);
            converter.convert(value);
            return result;
        }

        template <typename T>
        EJson ConvertValue(const EVector<T>& value)
        {
            EJson result = EJson::array();
            for (const T& entry : value)
            {
                result.push_back(ConvertValue(entry));
            }
            return result;
        }

        template <class Obj, class Field>
        void StructJsonConverter::operator() (const Obj* obj, const char* name, const Field& field) {
            fRef[name] = ConvertValue(field);
        }


        void ConvertObject(const EJson& ref, bool* value);
        void ConvertObject(const EJson& ref, i32* value);
        void ConvertObject(const EJson& ref, float* value);
        void ConvertObject(const EJson& ref, double* value);
        void ConvertObject(const EJson& ref, EString* value);
        void ConvertObject(const EJson& ref, EString* value);
        void ConvertObject(const EJson& ref, EVec2* value);
        void ConvertObject(const EJson& ref, EVec3* value);
        void ConvertObject(const EJson& ref, EVec4* value);

        template <typename T>
        auto ConvertObject(const EJson& json_object, T* value)
        -> decltype(T::_reflect_arg_count, void())
        {
            JsonStructConverter converter(json_object);
            converter.convert(value);
        }

        template <typename T>
        void ConvertObject(const EJson& ref, EVector<T>* value)
        {
            if (ref.is_array())
            {
                value->clear();
                for (const EJson& entry : ref)
                {
                    T newValue;
                    ConvertObject(entry, &newValue);
                    value->push_back(newValue);
                }
            }
        }

        template <class Obj, class Field>
        void JsonStructConverter::operator() (Obj* obj, const char* name, Field& field)
        {
            if (fRef.find(name)!=fRef.end())
            {
                JSHelper::ConvertObject(fRef[name], &field);
            }
        }
    }

}