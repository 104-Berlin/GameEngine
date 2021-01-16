#define ENGINE_NO_LIB
#include "Engine.h"

#ifdef __cplusplus
    #define EXTERN_C extern "C" 
#else
    #define EXTERN_C
#endif

#define EXPORT_API  EXTERN_C __attribute__((visibility("default")))


EXPORT_API void LoadExtension()
{
    std::cout << "Loaded animation extension" << std::endl;
}

