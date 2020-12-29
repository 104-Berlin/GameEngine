#include "Engine.h"

using namespace Engine;



int main(int argc, char const *argv[])
{   
    EResource res(Path::Join("Hello", "world.rc"));
    std::cout << res.GetNameIdent() << std::endl;

    EApplication::gApp();

    ERef<EScene> startScene = EMakeRef(EScene, "Start Scene");
    
    EVector<EMesh::EVertex> vertices = {
           { {-1,  1, 1},         {0.0f, 0.0f, 1.0f}, {0, 1}},
            {{-1, -1, 1},         {0.0f, 0.0f, 1.0f}, {0, 0}},
            {{ 1, -1, 1},         {0.0f, 0.0f, 1.0f}, {1, 0}},
            {{ 1,  1, 1},         {0.0f, 0.0f, 1.0f}, {1, 1}},
            
            {{-1,  1, -1},        {0.0f, 0.0f, -1.0f}, {0, 1}},
            {{-1, -1, -1},        {0.0f, 0.0f, -1.0f}, {0, 0}},
            {{ 1, -1, -1},        {0.0f, 0.0f, -1.0f}, {1, 0}},
            {{ 1,  1, -1},        {0.0f, 0.0f, -1.0f}, {1, 1}},
            
            
            
            {{1, -1,  1},          {1.0f, 0.0f, 0.0f}, {0, 1}},
            {{1, -1, -1},          {1.0f, 0.0f, 0.0f}, {0, 0}},
            {{1,  1, -1},          {1.0f, 0.0f, 0.0f}, {1, 0}},
            {{1,  1,  1},          {1.0f, 0.0f, 0.0f}, {1, 1}},

            {{-1, -1,  1},         {-1.0f, 0.0f, 1.0f}, {0, 1}},
            {{-1, -1, -1},         {-1.0f, 0.0f, 1.0f}, {0, 0}},
            {{-1,  1, -1},         {-1.0f, 0.0f, 1.0f}, {1, 0}},
            {{-1,  1,  1},         {-1.0f, 0.0f, 1.0f}, {1, 1}},


            {{-1,  1,  1},         {0.0f, 1.0f, 0.0f}, {0, 1}},
            {{-1,  1, -1},         {0.0f, 1.0f, 0.0f}, {0, 0}},
            {{ 1,  1, -1},         {0.0f, 1.0f, 0.0f}, {1, 0}},
            {{ 1,  1,  1},         {0.0f, 1.0f, 0.0f}, {1, 1}},

            {{-1, -1,  1},         {0.0f, -1.0f, 0.0f}, {0, 1}},
            {{-1, -1, -1},         {0.0f, -1.0f, 0.0f}, {0, 0}},
            {{ 1, -1, -1},         {0.0f, -1.0f, 0.0f}, {1, 0}},
            {{ 1, -1,  1},         {0.0f, -1.0f, 0.0f}, {1, 1}},
    };

    EVector<u32> indices = {
        0, 1, 2,
        2, 3, 0,
        
        4, 5, 6,
        6, 7, 4,
        
        8, 9, 10,
        10, 11, 8,
        
        12, 13, 14,
        14, 15, 12,
        
        16, 17, 18,
        18, 19, 16,
        
        20, 21, 22,
        22, 23, 20        
    };

    EVector<EMesh::EVertex> vertices_2 = {
        {{-0.5f, -0.5f, -1.0f}, {0, 0, 0}, {0, 0}},
        {{-0.5f,  0.5f, -1.0f}, {0, 0, 0}, {0, 0}},
        {{ 0.5f,  0.5f, -1.0f}, {0, 0, 0}, {0, 0}},
        {{ 0.5f, -0.5f, -1.0f}, {0, 0, 0}, {0, 0}},
    };

    EVector<u32> indices_2 = {
        0, 1, 2,
        2, 3, 0
    };

    EObject cameraObject1 = startScene->CreateObject();
    cameraObject1.AddComponent<ENameComponent>("Camera Object 1");
    cameraObject1.AddComponent<ECameraComponent>(true);

    EObject cameraObject2 = startScene->CreateObject();
    cameraObject2.AddComponent<ENameComponent>("Camera Object 2");
    cameraObject2.AddComponent<ECameraComponent>(false);

    /*EObject cameraObject3 = startScene->CreateObject();
    cameraObject3.AddComponent<ENameComponent>("Camera Object 3");
    cameraObject3.AddComponent<ECameraComponent>(false);

    EObject cameraObject4 = startScene->CreateObject();
    cameraObject4.AddComponent<ENameComponent>("Camera Object 4");
    cameraObject4.AddComponent<ECameraComponent>(false);*/

    EObject object1 = startScene->CreateObject();
    object1.AddComponent<ENameComponent>("Object 1");
    object1.AddComponent<TestComponent>();
    object1.AddComponent<EMeshComponent>();
    object1.GetComponent<EMeshComponent>().Mesh.SetValue(EMakeRef(EMesh, "TestMesh", vertices, indices));

    EApplication::gApp().Start(startScene);
    return 0;
}
