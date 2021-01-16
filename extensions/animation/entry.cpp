#include <iostream>

#ifdef __cplusplus
    #define EXTERN_C extern "C" 
#else
    #define EXTERN_C
#endif

#ifndef EXPORT_API
#define EXPORT_API  EXTERN_C __attribute__((visibility("default")))
#endif


EXPORT_API void LoadExtension()
{
    std::cout << "Loaded animation extension" << std::endl;
}
