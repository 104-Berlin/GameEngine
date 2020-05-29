

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <math.h>

typedef int_fast16_t i16;
typedef int_fast32_t i32;
typedef int_fast64_t i64;
typedef uint_fast16_t u16;
typedef uint_fast32_t u32;
typedef uint_fast64_t u64;
typedef uint_fast8_t byte;

typedef std::string EString;

template <typename T>
using EVector = std::vector<T>;


//------------------------------------------------------------------
// Extern Dependencies

#include "../glad/include/glad/glad.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>



#include "graphics/engine_window.h"