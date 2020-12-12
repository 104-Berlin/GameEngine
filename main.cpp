#include "Engine.h"

using namespace Engine;



int main(int argc, char const *argv[])
{   
    EApplication::gApp();

    EScene startScene("Start Scene");
    
    

    startScene.CreateComponent<EComponent>(startScene.CreateNewObject("Test object 1"));
    
    startScene.CreateNewObject("Test object 2");
    startScene.CreateNewObject("Test object 3");
    startScene.CreateNewObject("Test object 4");
    startScene.CreateNewObject("Test object 5");
    startScene.CreateNewObject("Test object 6");
    startScene.CreateNewObject("Test object 7");
    startScene.CreateNewObject("Test object 8");
    startScene.CreateNewObject("Test object 9");

    EApplication::gApp().Start(&startScene);

    return 0;
}
