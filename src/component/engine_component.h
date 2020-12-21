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
            (EObjectProperty<ETexture2D>, Texture)
        )
        TestComponent()
            : Boolean("Boolean"), Float("Float"), Double("Double"), Vector3("Vector3"), Vector4("Vector4"), StringValue("StringValue"), Texture("Texture")
            {}
        TestComponent(const TestComponent&) = default;
    };

    struct EUUIDComponent
    {
        REFLACTABLE(
            (EProperty<EUUID>, UUID)
        )
        
        EUUIDComponent(const EUUIDComponent&) = default;
        EUUIDComponent(const EUUID& uuid)
            : UUID("UUID", uuid)
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
            glm::quat quat = glm::quat(Rotation.GetValue());
            result *= glm::translate(EMat4(1.0f), Position.GetValue());
            result *= glm::scale(EMat4(1.0f), Scale.GetValue());
            result *= glm::toMat4(glm::conjugate(quat));
            return result;
        }
    };

    struct ENameComponent
    {
        REFLACTABLE(
            (EProperty<EString>, Name)
        )
        
        ENameComponent()
            : Name("Name", "Unknown")
        {}
        ENameComponent(const ENameComponent&) = default;

        ENameComponent(const EString& name)
            : Name("Name", name)
        {}
    };

    struct EMeshComponent
    {
        REFLACTABLE(
            (ERef<EMesh>, Mesh)
        )

        EMeshComponent() = default;
        EMeshComponent(const EMeshComponent&) = default;

    };

    struct ECameraComponent
    {
        REFLACTABLE(
            (ERef<ECamera>, Camera),
            (EProperty<bool>, Active)
        )

        ECameraComponent(ERef<ECamera> camera) : Camera(camera), Active("Active"){};
        ECameraComponent(const ECameraComponent&) = default;
    };

}