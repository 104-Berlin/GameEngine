#include "Engine.h"

#ifdef __cplusplus
    #define EXTERN_C extern "C" 
#else
    #define EXTERN_C
#endif

#define EXPORT_API  EXTERN_C __attribute__((visibility("default")))


struct SomeStruct
{
    
};

struct SomeComponent
{
    REFLACTABLE(
        (int, x)
    )
};



EXPORT_API void LoadExtension(SomeStruct* data)
{
    std::cout << "Loaded animation extension" << std::endl;

    REGISTER_COMPONENT(SomeComponent);
}

