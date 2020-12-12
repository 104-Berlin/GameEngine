#include "Engine.h"

using namespace Engine;

EMesh::EMesh(const EString& name, const EString& path)
    : EResource(name, path)
{

}

EMesh::~EMesh()
{

}

bool EMesh::OnLoad()
{
    return false;
}