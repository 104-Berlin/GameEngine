#include "Engine.h"

using namespace Engine;



int main(int argc, char const *argv[])
{   
    EApplication::gApp();

    ERef<EScene> startScene = EMakeRef(EScene, "Start Scene");

    EApplication::gApp().Start(startScene);
    return 0;
}
