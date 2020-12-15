#include "Engine.h"

using namespace Engine;



int main(int argc, char const *argv[])
{   
    EApplication::gApp();

    ERef<EScene> startScene = EMakeRef(EScene, "Start Scene");

    EObject object1 = startScene->CreateObject();
    object1.AddComponent<ENameComponent>("Object 1");

    EApplication::gApp().Start(startScene);
    return 0;
}
