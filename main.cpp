#include "Engine.h"

using namespace Engine;



int main(int argc, char const *argv[])
{   
    EApplication app;

    EScene startScene("Start Scene");
    
    ESceneObject* object_1 = new ESceneObject("Object 1");
    
    
    startScene.AddObject(object_1);

    app.Start(&startScene);

    return 0;
}
