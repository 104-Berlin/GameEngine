#include "Engine.h"
 
static const char* vertex_shader_text =
"#version 120\n"
"attribute vec3 vPos;\n"
"attribute vec3 color;\n"

"uniform mat4 v_matrix = mat4(1.0);\n"
"uniform mat4 p_matrix = mat4(1.0);\n"

"varying vec3 oColor;\n"

"void main()\n"
"{\n"
"    gl_Position = p_matrix * v_matrix * vec4(vPos + vec3(3, 3, 2), 1.0);\n"
"   oColor = color;\n"
"}\n";
 
static const char* fragment_shader_text =
"#version 120\n"

"varying vec3 oColor;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(oColor, 1.0);\n"
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

    ECamera cam(glm::perspectiveFovLH_NO(30.0f, 1270.0f, 720.0f, 0.0001f, 100000.0f));

    std::vector<float> vertices = {    -1,  1, 1.f,         1.0f, 0.0f, 0.0f,
                                       -1, -1, 1.f,         1.0f, 0.0f, 0.0f,
                                        1, -1, 1.f,         1.0f, 0.0f, 0.0f,
                                        1,  1, 1.f,         1.0f, 0.0f, 0.0f,
                                        
                                        -1,  1, -1.f,       0.0f, 1.0f, 0.0f,
                                       -1, -1, -1.f,        0.0f, 1.0f, 0.0f,
                                        1, -1, -1.f,        0.0f, 1.0f, 0.0f,
                                        1,  1, -1.f,        0.0f, 1.0f, 0.0f,
                                        
                                        
                                        
                                        1, -1,  1,          0.0f, 0.0f, 1.0f,
                                        1, -1, -1,          0.0f, 0.0f, 1.0f,
                                        1,  1, -1,          0.0f, 0.0f, 1.0f,
                                        1,  1,  1,          0.0f, 0.0f, 1.0f,

                                       -1, -1,  1,          1.0f, 0.0f, 1.0f,
                                       -1, -1, -1,          1.0f, 0.0f, 1.0f,
                                       -1,  1, -1,          1.0f, 0.0f, 1.0f,
                                       -1,  1,  1,          1.0f, 0.0f, 1.0f,


                                        -1,  1,  1,         0.0f, 1.0f, 1.0f,
                                        -1,  1, -1,         0.0f, 1.0f, 1.0f,
                                         1,  1, -1,         0.0f, 1.0f, 1.0f,
                                         1,  1,  1,         0.0f, 1.0f, 1.0f,
 
                                        -1, -1,  1,         1.0f, 1.0f, 0.0f,
                                        -1, -1, -1,         1.0f, 1.0f, 0.0f,    
                                         1, -1, -1,         1.0f, 1.0f, 0.0f,
                                         1, -1,  1,         1.0f, 1.0f, 0.0f,
                                 };
    
    std::vector<u32> indices = {0, 1, 2,
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
                                22, 23, 20};
    

    EVertexBuffer* vb = EVertexBuffer::Create(&vertices[0], vertices.size() * sizeof(float));
    EIndexBuffer* ib = EIndexBuffer::Create(&indices[0], indices.size());
    EShader* shader = EShader::Create(vertex_shader_text, fragment_shader_text);
 

    IN_RENDER({
        glEnable(GL_DEPTH_TEST);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                             6 * sizeof(float), (void*) 0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                             6 * sizeof(float), (void*) (3*sizeof(float)));

    })
    glm::mat4 v_mat = glm::mat4(1.0f);
    glm::mat4 p_mat = glm::mat4(1.0f);
    /* Loop until the user closes the window */
    while (!window.IsClosed())
    {
        IN_RENDER({
            glClearColor(1.0, 1.0, 1.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        })
        cam.Update(&window);
        v_mat = cam.GetViewMatrix();
        p_mat = cam.GetProjectionMatrix();
        shader->Bind();
        shader->SetUniformMat4("p_matrix", p_mat);
        shader->SetUniformMat4("v_matrix", v_mat);
        
        vb->Bind();
        ib->Bind();
        
        
        IN_RENDER1(indices, {
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);
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
