#pragma once

namespace Engine {

    class ESpriteComponent : public EComponent
    {
    private:
        EObjectProperty<ESprite>    fSprite;
        EObjectProperty<EShader>    fShader;
    public:
        ESpriteComponent();
        virtual ~ESpriteComponent();

        void SetSprite(ESprite* sprite);

        virtual void OnRender() override;
    };

}