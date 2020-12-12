#include "Engine.h"

using namespace Engine;



int main(int argc, char const *argv[])
{   
    EApplication::gApp();

    EScene startScene("Start Scene");

    ESprite* sprite = new ESprite("Test Sprite","TILE.png");
    if (!startScene.LoadResource(sprite))
    {
        std::cout << "Cant load sprite" << std::endl;
    }

    ESceneObject* object = startScene.CreateNewObject("Test object 1");

    ESpriteComponent* spriteComponent = startScene.CreateComponent<ESpriteComponent>(object);
    spriteComponent->SetSprite(sprite);
    
    EApplication::gApp().Start(&startScene);

    
    delete sprite;
    return 0;
}
