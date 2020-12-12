#include "Engine.h"

namespace Engine { namespace JSHelper {

    bool HasParam(const EJson& ref, const EString& param)
    {
        return std::find(ref.begin(), ref.end(), param) != ref.end();
    }

    EJson ConvertValue(const bool value)
    {
        return value;
    }

    EJson ConvertValue(const i32 value)
    {
        return value;
    }

    EJson ConvertValue(const float value)
    {
        return value;
    }

    EJson ConvertValue(const double value)
    {
        return value;
    }

    EJson ConvertValue(const EString& value)
    {
        return value;
    }

    EJson ConvertValue(const EUUID& value)
    {
        return ConvertValue(value.ToString());
    }

    EJson ConvertValue(const EVec2& value)
    {
        EJson result = EJson::object();
        result["X"] = value.x;
        result["Y"] = value.y;
        return result;
    }

    EJson ConvertValue(const EVec3& value)
    {
        EJson result = EJson::object();
        result["X"] = value.x;
        result["Y"] = value.y;
        result["Z"] = value.z;
        return result;
    }

    EJson ConvertValue(const EVec4& value)
    {
        EJson result = EJson::object();
        result["X"] = value.x;
        result["Y"] = value.y;
        result["Z"] = value.z;
        result["W"] = value.w;
        return result;
    }

    EJson ConvertValue(EObject* object)
    {
        if (object)
        {
            return ConvertValue(object->GetUuid());
        }
        else
        {
            return ConvertValue(EUUID());
        }
    }

    void ConvertObject(const EJson& ref, bool* value)
    {
        if (ref.is_boolean())
        {
            *value = ref.get<bool>();
        }
    }

    void ConvertObject(const EJson& ref, i32* value)
    {
        if (ref.is_number_integer())
        {
            *value = ref.get<i32>();
        }
    }

    void ConvertObject(const EJson& ref, float* value)
    {
        if (ref.is_number_float())
        {
            *value = ref.get<float>();
        }
    }

    void ConvertObject(const EJson& ref, double* value)
    {
        if (ref.is_number_float()) 
        {
            *value = ref.get<double>();
        }
    }

    void ConvertObject(const EJson& ref, EString* value)
    {
        if (ref.is_string())
        {
            *value = ref.get<EString>();
        }
    }

    void ConvertObject(const EJson& ref, EUUID* value)
    {
        if (ref.is_string())
        {
            EString stringVal = ref.get<EString>();
            EUUID uuid;
            if (uuid.FromString(stringVal))
            {
                *value = uuid;
            }
        }        
    }

    void ConvertObject(const EJson& ref, EVec2* value)
    {
        float x = 0;
        float y = 0;
        if (HasParam(ref, "X")) { ConvertObject(ref["X"], &x);}
        if (HasParam(ref, "Y")) { ConvertObject(ref["Y"], &y);}
        value->x = x;
        value->y = y;
    }

    void ConvertObject(const EJson& ref, EVec3* value)
    {
        float x = 0;
        float y = 0;
        float z = 0;
        if (HasParam(ref, "X")) { ConvertObject(ref["X"], &x);}
        if (HasParam(ref, "Y")) { ConvertObject(ref["Y"], &y);}
        if (HasParam(ref, "Z")) { ConvertObject(ref["Z"], &z);}
        value->x = x;
        value->y = y;
        value->z = z;
    }

    void ConvertObject(const EJson& ref, EVec4* value)
    {
        float x = 0;
        float y = 0;
        float z = 0;
        float w = 0;
        if (HasParam(ref, "X")) { ConvertObject(ref["X"], &x);}
        if (HasParam(ref, "Y")) { ConvertObject(ref["Y"], &y);}
        if (HasParam(ref, "Z")) { ConvertObject(ref["Z"], &z);}
        if (HasParam(ref, "Z")) { ConvertObject(ref["Z"], &w);}
        value->x = x;
        value->y = y;
        value->z = z;
        value->w = w;
    }

    void ConvertObject(const EJson& ref, ESceneObject** sceneObject)
    {
        if (ref.is_string())
        {
            EUUID uuid;
            if (uuid.FromString(ref.get<EString>()))
            {
                *sceneObject = EApplication::gApp().GetActiveScene()->GetByUuid(uuid);
            }
        }
    }

    void ConvertObject(const EJson& ref, EResource** sceneObject)
    {
        if (ref.is_string())
        {
            EUUID uuid;
            if (uuid.FromString(ref.get<EString>()))
            {
                *sceneObject = EApplication::gApp().GetActiveScene()->GetResource(uuid);
            }
        }
    }

    void ConvertObject(const EJson& ref, EShader** sceneObject)
    {
        ConvertObject(ref, (EResource**) sceneObject);
    }

    void ConvertObject(const EJson& ref, ESprite** sceneObject)
    {
        ConvertObject(ref, (EResource**) sceneObject);    
    }
} }