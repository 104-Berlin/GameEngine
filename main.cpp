#include "Engine.h"
 
static const char* vertex_shader_text =
"#version 120\n"
"attribute vec2 vPos;\n"
"attribute vec3 vCol;\n"


"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";
 
static const char* fragment_shader_text =
"#version 120\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";


using namespace Engine;

#define GL_ERR(fn) fn;\
GLenum err = glGetError();\
if (err != GL_NO_ERROR){\
std::cout << "GL_ERR: " << glGetString(err) << std::endl;\
}

int main(int argc, char const *argv[])
{   
    EWindow window(EWindowProp("Hello World", 1270, 720));
    ERenderer::Init();


    std::vector<float> vertices = { -0.6f, -0.4f, 1.f, 0.f, 0.f ,
                                    0.6f, -0.4f, 0.f, 1.f, 0.f ,
                                    0.f,  0.6f, 0.f, 0.f, 1.f };
    
    std::vector<u32> indices = {0, 1, 2};
    

    EVertexBuffer* vb = EVertexBuffer::Create(&vertices[0], vertices.size() * sizeof(float));
    EIndexBuffer* ib = EIndexBuffer::Create(&indices[0], indices.size());
    EShader* shader = EShader::Create(vertex_shader_text, fragment_shader_text);
 
    IN_RENDER({
        
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
                              5 * sizeof(float), (void*) 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
        5 * sizeof(float), (void*) (sizeof(float) * 2));
    })

    /* Loop until the user closes the window */
    while (!window.IsClosed())
    {
        IN_RENDER({
            glClearColor(1.0, 1.0, 1.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
        })
        
        shader->Bind();
        vb->Bind();
        ib->Bind();
        
        
        IN_RENDER({
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);
        })

        ERenderer::WaitAndRender();
        
        
        window.Update();
    }
    
    delete ib;
    delete vb;
    delete shader;

    glfwTerminate();
    std::cout << "Hello World!" << std::endl; 
    return 0;
}
