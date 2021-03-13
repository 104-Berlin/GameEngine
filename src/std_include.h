#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <math.h>
#include <chrono>
#include <stdarg.h>
#include <memory>
#include <filesystem>
#include <queue>
#include <thread>
#include <set>

#ifdef M_PI
#undef M_PI
#endif

#define M_PI 3.14159f


#define BIT(x) (1 << x)
#define DEG_TO_RAD (M_PI / 180.0)

#ifdef EWIN
    #ifdef EEXPORT
        #define E_API __declspec(dllexport)
    #else
        #define E_API __declspec(dllimport)
    #endif
#else
    #define E_API
#endif

#ifdef EWIN
#include <Windows.h>
#include <mutex>
#include <atomic>
#else
#include <dlfcn.h>
#include <unistd.h>
#endif


typedef int_fast16_t i16;
typedef int_fast32_t i32;
typedef int_fast64_t i64;
typedef uint_fast8_t u8;
typedef uint_fast16_t u16;
typedef uint_fast32_t u32;
typedef uint_fast64_t u64;
typedef uint_fast8_t byte;

typedef std::string EString;

template <typename T>
using EVector = std::vector<T>;

template <typename T>
using ESet = std::set<T>;

template <typename K, typename V>
using EMap = std::map<K, V>;

template <typename K, typename V, class Hash = std::hash<K>, class Pred = std::equal_to<K>, class Alloc = std::allocator< std::pair<const K, V>>>
using EUnorderedMap = std::unordered_map<K, V, Hash, Pred, Alloc>;

template <typename T>
using EQueue = std::queue<T>;

template <typename T>
using EScope = std::unique_ptr<T>;
#define EMakeScope(Type, ...) std::make_unique<Type>(__VA_ARGS__)


template <typename T>
using ERef = std::shared_ptr<T>;
#define EMakeRef(Type, ...) std::make_shared<Type>(__VA_ARGS__)


template <typename T>
using EWeakRef = std::weak_ptr<T>;

const char kPathSeparator =
#ifdef EWIN
                            '\\';
#else
                            '/';
#endif


#include "properties/json.hpp"
#include "scene/entt.hpp"


#include "../deps/glm/glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "../deps/glm/glm/gtx/quaternion.hpp"


#include "../deps/imgui/imgui.h"
#include "../deps/imguizmo/ImGuizmo.h"



// Entities are saved in a registry and can have components attached to
typedef entt::entity        EEntity;

typedef glm::vec2       EVec2;
typedef glm::vec3       EVec3;
typedef glm::vec4       EVec4;
typedef glm::mat4       EMat4;

typedef EVec4           EColor;
typedef nlohmann::json  EJson;
