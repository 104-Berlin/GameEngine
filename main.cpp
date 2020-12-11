#include "Engine.h"

using namespace Engine;



int main(int argc, char const *argv[])
{   
    EApplication::gApp();

    EScene startScene("Start Scene");
    
    ESceneObject* object_1 = startScene.CreateNewObject("Test object 1");
    ESceneObject* object_2 = startScene.CreateNewObject("Test object 2");
    ESceneObject* object_3 = startScene.CreateNewObject("Test object 3");
    ESceneObject* object_4 = startScene.CreateNewObject("Test object 4");
    ESceneObject* object_5 = startScene.CreateNewObject("Test object 5");

    object_3->SetChild(object_5);
    object_5->SetParent(object_3);
    object_5->SetPrev(nullptr);
    object_4->SetNext(nullptr);
    

    EApplication::gApp().Start(&startScene);

    return 0;
}
