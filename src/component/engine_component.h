#pragma once

namespace Engine {

    struct TestComponent
    {
        REFLACTABLE(
            (bool, Boolean),
            (float, Float),
            (double, Double),
            (EVec3, Vector3),
            (EVec4, Vector4),
            (EString, StringValue)
        )
        TestComponent() = default;
        TestComponent(const TestComponent&) = default;
    };

    struct EUUIDComponent
    {
        REFLACTABLE(
            (EUUID, UUID)
        )
        
        EUUIDComponent(const EUUIDComponent&) = default;
        EUUIDComponent(const EUUID& uuid)
            : UUID(uuid)
        {}
        
    };

    struct ETransformComponent
    {
        REFLACTABLE(
            (EVec3, Position),
            (EVec3, Rotation),
            (EVec3, Scale)
        )

        ETransformComponent(const EVec3& position = EVec3(0.0f, 0.0f, 0.0f), const EVec3& rotation = EVec3(0.0f, 0.0f, 0.0f), const EVec3& scale = EVec3(1.0f, 1.0f, 1.0f))
            : Position(position), Rotation(rotation), Scale(scale)
        {}
        ETransformComponent(const ETransformComponent&) = default;


        operator EMat4 () const
        {
            EMat4 result = EMat4(1.0f);
            glm::quat quat = glm::quat(Rotation);
            result *= glm::translate(EMat4(1.0f), Position);
            result *= glm::scale(EMat4(1.0f), Scale);
            result *= glm::toMat4(glm::conjugate(quat));
            return result;
        }
    };

    struct ENameComponent
    {
        REFLACTABLE(
            (EString, Name)
        )
        
        ENameComponent()
            : Name("Unknown")
        {}
        ENameComponent(const ENameComponent&) = default;

        ENameComponent(const EString& name)
            : Name(name)
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
            (bool, Active)
        )

        ECameraComponent(ERef<ECamera> camera) : Camera(camera){};
        ECameraComponent(const ECameraComponent&) = default;
    };

}