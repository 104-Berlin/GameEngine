#include "Engine.h"

using namespace Engine;

static const char* vertex_shader_text =
"#version 330 core\n"
"layout(location = 0) in vec2 Position;\n"
"layout(location = 1) in vec2 UV;\n"

"out vec2 TransUv;\n"

"void main()\n"
"{\n"
"    gl_Position = vec4(Position, 0.0, 1.0);\n"
"   TransUv = UV;\n"
"}\n";
 
static const char* fragment_shader_text =
"#version 330 core\n"

"in vec2 TransUv;\n"

"out vec4 FinalColor;\n"

"uniform sampler2D sampler;"

"void main()\n"
"{\n"
"    FinalColor = texture(sampler, TransUv);\n"
"    //FinalColor = vec4(TransUv, 0.0, 1.0);\n"
"}\n";


ESpriteComponent::ESpriteComponent()
    : EComponent(),
        fSprite(this, "Sprite"),
        fShader(this, "Shader")
{
    SetName("Sprite Component");

    EShader* shader = EShader::Create(vertex_shader_text, fragment_shader_text);
    fShader.SetValue(shader);
}

ESpriteComponent::~ESpriteComponent()
{
    EShader* shader = fShader.GetValue();
    delete shader;
}

void ESpriteComponent::SetSprite(ESprite* sprite)
{
    fSprite.SetValue(sprite);
}

void ESpriteComponent::OnRender()
{
    if (!fShader.GetValue()) { return; }

    fShader.GetValue()->Bind();
    fShader.GetValue()->SetUniform1i("sampler", 0);

    fSprite.GetValue()->Draw();
}