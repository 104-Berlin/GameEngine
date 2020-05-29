#include "Engine.h"


static const struct
{
    float x, y;
    float r, g, b;
} vertices[3] =
{
    { -0.6f, -0.4f, 1.f, 0.f, 0.f },
    {  0.6f, -0.4f, 0.f, 1.f, 0.f },
    {   0.f,  0.6f, 0.f, 0.f, 1.f }
};
 
static const char* vertex_shader_text =
"#version 330\n"
"attribute vec3 vCol;\n"
"layout (location = 0) in vec2 position\n"
"layout (location = 1) in vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(position, 0.0, 1.0);\n"
"    color = color;\n"
"}\n";
 
static const char* fragment_shader_text =
"#version 330\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";


using namespace Engine;

int main(int argc, char const *argv[])
{   
    EWindow window(EWindowProp("Hello World", 1270, 720));


    GLuint vertex_buffer;
    GLint mvp_location, vpos_location, vcol_location;


    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
 
    EShader* shader = EShader::Create(vertex_shader_text, fragment_shader_text);
 
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
                          sizeof(vertices[0]), (void*) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
    sizeof(vertices[0]), (void*) (sizeof(float) * 2));


    /* Loop until the user closes the window */
    while (!window.IsClosed())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        shader->Bind();
        
        glDrawArrays(GL_TRIANGLES, 0, 3);

        

        window.Update();
    }

    delete shader;

    glfwTerminate();
    std::cout << "Hello World!" << std::endl; 
    return 0;
}
