#pragma once

namespace Engine {

    struct TestComponent
    {
        REFLACTABLE(
            (EProperty<bool>, Boolean),
            (EProperty<float>, Float),
            (EProperty<double>, Double),
            (EProperty<EVec3>, Vector3),
            (EProperty<EVec4>, Vector4),
            (EProperty<EString>, StringValue),
            (EResourceProperty<ETexture2D>, Texture)
        )
        TestComponent()
            : Boolean("Boolean"), Float("Float"), Double("Double"), Vector3("Vector3"), Vector4("Vector4"), StringValue("StringValue"), Texture("Texture")
            {}
        TestComponent(const TestComponent&) = default;
    };

    struct ETagComponent
    {
        REFLACTABLE(
            (EProperty<EUUID>, UUID),
            (EProperty<EString>, Name)
        )
        
        ETagComponent(const ETagComponent&) = default;
        ETagComponent(const EString& name = "Empty", const EUUID& uuid = EUUID())
            : Name("Name", name), UUID("UUID", uuid)
        {}
        
    };

    struct ETransformComponent
    {
        REFLACTABLE(
            (EProperty<EVec3>, Position),
            (EProperty<EVec3>, Rotation),
            (EProperty<EVec3>, Scale)
        )

        ETransformComponent(const EVec3& position = EVec3(0.0f, 0.0f, 0.0f), const EVec3& rotation = EVec3(0.0f, 0.0f, 0.0f), const EVec3& scale = EVec3(1.0f, 1.0f, 1.0f))
            : Position("Position", position), Rotation("Rotation", rotation), Scale("Scale", scale)
        {}
        ETransformComponent(const ETransformComponent&) = default;


        operator EMat4 () const
        {
            EMat4 result = EMat4(1.0f);
            EVec3 rotationInRadian = Rotation.GetValue();
            rotationInRadian.x *= DEG_TO_RAD;
            rotationInRadian.y *= DEG_TO_RAD;
            rotationInRadian.z *= DEG_TO_RAD;

            glm::quat quat = glm::quat(rotationInRadian);
            result *= glm::translate(EMat4(1.0f), Position.GetValue());
            result *= glm::scale(EMat4(1.0f), Scale.GetValue());
            result *= glm::toMat4(glm::conjugate(quat));
            return result;
        }
    };

    struct EMeshComponent
    {
        REFLACTABLE(
            (EResourceProperty<EMesh>, Mesh)
        )

        EMeshComponent() = default;
        EMeshComponent(const EMeshComponent&) = default;

    };

    

    struct ECameraComponent
    {
        enum class CameraMode : i32
        {
            ORTHOGRAPHIC,
            PERSPECTIVE
        };

        REFLACTABLE(
            (EObjectProperty<ECamera>, Camera),
            (EProperty<float>, FOV),
            (EProperty<bool>, Active)
        )

        ECameraComponent()
        {
            Camera.SetValue(EMakeRef(ECamera, glm::perspective(30.0f, 16.0f / 9.0f, 0.0001f, 100000.0f)));
            FOV = 30;
        }

        ECameraComponent(bool active)
            : ECameraComponent()
        {
            Active.SetValue(active);
            FOV = 30;
            Camera.SetValue(EMakeRef(ECamera, glm::perspective(30.0f, 16.0f / 9.0f, 0.0001f, 100000.0f)));
        }
        ECameraComponent(const ECameraComponent&) = default;
    };

    struct Test
    {
        EObjectProperty<ECamera> Camera = EObjectProperty<ECamera>("Camera");
    };

}