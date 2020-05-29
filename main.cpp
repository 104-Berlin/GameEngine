#include "Engine.h"


using namespace Engine;

int main(int argc, char const *argv[])
{   
    EWindow window("Test Window", 1270, 720);
    window.Show();

    float position[] = {
        -0.5f, -0.5f, 
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    u32 indicies[] = {
        0, 1, 2
    };


    unsigned int vbo, ibo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), position, GL_STATIC_DRAW);


    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(u32), indicies, GL_STATIC_DRAW);

    std::cout << glGetString(GL_VERSION) << std::endl;

    /* Loop until the user closes the window */
    while (window.IsOpen())
    {
        window.Clear();

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);
        

        window.Update();
    }

    glfwTerminate();
    std::cout << "Hello World!" << std::endl; 
    return 0;
}
