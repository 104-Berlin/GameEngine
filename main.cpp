#ifdef EEXPORT
#undef EEXPORT
#endif
#include "Engine.h"

using namespace Engine;




int main(int argc, char const *argv[])
{  
    EApplication::gApp();
    
    EApplication::gApp().Start();
    return 0;
}
