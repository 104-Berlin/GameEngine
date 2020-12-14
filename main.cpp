#include "Engine.h"

using namespace Engine;



int main(int argc, char const *argv[])
{   
    EApplication::gApp();

    EScene startScene("Start Scene");

    EApplication::gApp().Start(&startScene);
    return 0;
}
