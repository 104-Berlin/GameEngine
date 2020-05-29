#include <iostream>
#include <GLFW/glfw3.h>

void GL_ERROR()
{
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        std::cout << glGetString(err) << std::endl;
    }
}

int main(int argc, char const *argv[])
{   
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    float position[] = {
        -0.5f, -0.5f, 
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    int indicies[] = {
        0, 1, 2
    };



    unsigned int vbo, ibo;
    glGenBuffers(1, &vbo);
    GL_ERROR();
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    GL_ERROR();

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), position, GL_STATIC_DRAW);
    GL_ERROR();
    std::cout << glGetString(GL_VERSION) << std::endl;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    std::cout << "Hello World!" << std::endl; 
    return 0;
}
